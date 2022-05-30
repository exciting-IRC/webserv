#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <cstring>

inline int isTchar(int c) {
  
  return (std::isalpha(c) || std::isdigit(c) || std::strchr("!#$%&'*+-.^_`|~", c));
}

class ParserBase {
 public:
  ParserBase(std::istream &raw_input) : raw_input_(raw_input) {}
  virtual bool parse() = 0;

 protected:
  char peek() { return raw_input_.peek(); }
  void pop() { raw_input_.ignore(); }

 private:
  // cannot copyable
  ParserBase &operator=(const ParserBase &);
  ParserBase(const ParserBase &);

 private:
  std::istream &raw_input_;
};

class ABNFParser : public ParserBase {
 public:
  ABNFParser(std::istream &raw_input) : ParserBase(raw_input) {}

 private:
  // cannot copyable
  ABNFParser &operator=(const ABNFParser &);
  ABNFParser(const ABNFParser &);

 public:
  virtual bool parse() = 0;

 protected:
  // XXX 빠진 함수들 parseCTL(); parseOCTET;
  bool parseChar(char c) {
    if (peek() == c) {
      pop();
      return true;
    }
    return false;
  }

  char parseChar(int (*checker)(int)) {
    char c = peek();
    if (checker(c)) {
      pop();
      return c;
    }
    return '\0';
  }

  std::string parseString(int (*checker)(int)) {
    std::string str;
    for (char c = peek(); checker(c); pop(), c = peek()) {
      str.push_back(c);
    }
    return str;
  }

  bool parseTerminal(const char *s) {
    for (std::size_t i = 0; s[i]; ++i) {
      if (s[i] != peek()) {
        return false;
      }
      pop();
    }
    return true;
  }

  bool parseSP() { return parseChar(' '); }

  bool parseHTAB() { return parseChar('\t'); }

  bool parseDQUOTE() { return parseChar('"'); }

  bool parseCR() { return parseChar('\r'); }

  bool parseLF() { return parseChar('\n'); }

  bool parseCRLF() { return parseCR() && parseLF(); }

  char parseDIGIT() { return parseChar(std::isdigit); }
  std::string parseDIGITString() { return parseString(std::isdigit); }

  char parseALPHA() { return parseChar(std::isalpha); }
  std::string parseALPHAString() { return parseString(std::isalpha); }

  char parseVCHAR() { return parseChar(std::isprint); }
  std::string parseVCHARString() { return parseString(std::isprint); }

  char parseHexDigit() { return parseChar(std::isxdigit); }
  std::string parseHexDigitString() { return parseString(std::isxdigit); }
};

enum HttpMethod { kINVALID, kGET, kHEAD, kPOST, kDELETE };

struct RequestTarget {
  std::string path;
  std::string query;
};

struct HttpVersion {
  char major;
  char minor;
};

typedef std::map<std::string, std::string> HeaderMap;

struct HttpRequest {
  HttpMethod method;
  HttpVersion version;
  RequestTarget target;
  std::map<std::string, std::string> headers;
  std::string body;
};

class HttpParser : public ABNFParser {
 public:
  HttpParser(std::istream &raw_input) : ABNFParser(raw_input) {}

 private:
  // cannot copyable
  HttpParser &operator=(const HttpParser &);
  HttpParser(const HttpParser &);

 public:
  virtual bool parse() { return parseHttpMessage(); }

 private:
  char htoi(char hex) {
    hex = std::toupper(hex);
    if (hex > '9')
      return hex - ('A' - 10);
    return hex - '0';
  }

  std::string &decode(std::string &target) {
    std::size_t pos = 0;
    while ((pos = target.find('%', pos)) != std::string::npos) {
      if (pos + 2 >= target.size() || !std::isxdigit(target[pos + 1]) ||
          !std::isxdigit(target[pos + 2]))
        throw std::logic_error("Cannot decode given URI");
      char decoded = std::numeric_limits<char>::min();
      decoded += htoi(target[pos + 1]) * 16;
      decoded += htoi(target[pos + 2]);
      if (decoded < 0)
        decoded -= std::numeric_limits<char>::min();
      else
        decoded += std::numeric_limits<char>::min();
      target.replace(pos, 3, 1, decoded);
      ++pos;
    }
    return target;
  }

  bool parseHttpMessage() {
    if (!parseStartLine())
      return false;
    while (isTchar(peek())) {
      if (!parseHeaderField())
        return false;
    }
    return parseCRLF();
  }

  bool parseStartLine() { return parseRequestLine(); }

  bool parseRequestLine() {
    return parseMethod() && parseSP() && parseRequestTarget() && parseSP() && parseHttpVersion() &&
           parseCRLF();
  }

  bool parseMethod() {
    std::string methodString = parseALPHAString();

    request_.method = findMethodKind(methodString);
    return request_.method != kINVALID;
  }

  // absolute-path = 1*("/" segment) [ "?" query ]
  // segment       = *pchar
  // pchar         = unreserved | pct-encoded | sub-delims | ":" | "@"
  // unsreserved   = DIGIT | ALPHA | "." | "~" | "_" | "-"
  // pct-encoded   = % HEXDIG HEXDIG
  // sub-delims    = "!" | "$" | "&" | "'" | "(" | ")" | "*" | "+" | "," | ";" | "="

  bool isUnReserved(char c) {
    return std::isdigit(c) || std::isalpha(c) || c == '.' || c == '~' || c == '_' || c == '-';
  }

  bool isSubDelims(char c) {
    return c == '!' || c == '$' || c == '&' || c == '\'' || c == '(' || c == ')' || c == '*' ||
           c == '+' || c == ',' || c == ';' || c == '=';
  }

  bool isPChar(char c) {
    return isUnReserved(c) || isSubDelims(c) || c == ':' || c == '@' || c == '%' || c == '?' ||
           c == '/';
  }

  std::string parseURI() {
    std::string uri;

    for (char c = peek(); isPChar(c); pop(), c = peek()) {
      uri.push_back(c);
    }
    return uri;
  }

  bool parseRequestTarget() {
    std::string target = parseURI();

    if (target.empty() || target[0] != '/') {
      return false;
    }
    decode(target);
    size_t pos = target.find('?');
    request_.target.path = target.substr(0, pos);
    if (pos != std::string::npos) {
      request_.target.query = target.substr(pos + 1);
    }
    return true;
  }

  // "HTTP" "/" major "." minor (ex. HTTP/1.1)
  bool parseHttpVersion() {
    if (!parseTerminal("HTTP/"))
      return false;
    char major = parseDIGIT();
    if (major == '\0') {
      return false;
    }
    request_.version.major = major - '0';
    parseTerminal(".");
    char minor = parseDIGIT();
    if (minor == '\0') {
      return false;
    }
    request_.version.minor = minor - '0';
    return true;
  }

 public:
  HttpRequest request_;

 private:
  typedef std::map<std::string, HttpMethod> MethodMap;

  MethodMap getAllowedMethod() {
    MethodMap mm;

    mm.insert(MethodMap::value_type("GET", kGET));
    mm.insert(MethodMap::value_type("HEAD", kHEAD));
    mm.insert(MethodMap::value_type("POST", kPOST));
    mm.insert(MethodMap::value_type("DELETE", kDELETE));

    return mm;
  }

  HttpMethod findMethodKind(const std::string &method) {
    const static MethodMap allowedMethods = getAllowedMethod();

    MethodMap::const_iterator kindIter = allowedMethods.find(method);

    if (kindIter == allowedMethods.end())
      return kINVALID;
    return kindIter->second;
  }

  bool parseOWS() {
    for (char c = peek(); c == ' ' || c == '\t'; pop(), c = peek())
      ;
    return true;
  }

  bool parseBWS() { return parseOWS(); }

  bool parseRWS() {
    char c = peek();
    if (c != ' ' && c != '\t')
      return false;
    return parseOWS();
  }

  bool parseHeaderField() {
    HeaderMap::iterator fieldEntry = parseFieldName();
    if (fieldEntry == request_.headers.end())
      return false;
    return parseChar(':') && parseFieldValue(fieldEntry) && parseCRLF();
  }

  HeaderMap::iterator parseFieldName() {
    std::string fieldName = parseString(isTchar);
    if (fieldName.empty())
      return request_.headers.end();
    std::pair<HeaderMap::iterator, bool> r = request_.headers.insert(HeaderMap::value_type(fieldName, ""));
    if (r.second == false) {
      return request_.headers.end();
    }
    return r.first;
  }

  bool isFieldVchar(char c) {
    // VCHAR or obs-text
    return std::isprint(c) || c < 0;
  }

  // deallow obs-fold
  bool parseFieldValue(HeaderMap::iterator entry) {
    std::string &fieldValue = entry->second;

    for (char c = peek(); isFieldVchar(c) || c == '\t' || c == ' '; pop(), c = peek()) {
      fieldValue.push_back(c);
    }
    //strtrim(fieldValue)
    return true;
  }
  // bool parseStatusLine();
  //  bool parseMessageBody();
};