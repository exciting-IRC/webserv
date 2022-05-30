#ifndef PARSER_TOKENIZER_HPP
#define PARSER_TOKENIZER_HPP

#include <fstream>
#include <string>
#include <strutil/strutil.hpp>
#include <vector>

namespace util {

using std::string;
using std::vector;

struct token_t {
  enum e { kLeftBracket, kRightBracket, kTerminator, kWord, kUnset = -1 };
  static const string n[5];
};
const string token_t::n[5] = {"left bracket", "right bracket", "terminator",
                              "word", "unset"};

struct Token {
  token_t::e type;
  string value;
};

class Tokenizer {
 public:
 private:
  std::ifstream& infile_;
  vector<string> raw_;
  vector<Token> tokens_;

  void read_raw() {
    using namespace util;

    string line;
    while (getline(infile_, line)) {
      util::erase_from(line, "#");
      util::trim(line);
      if (line.empty())
        continue;

      vector<string> tmp = split(line, " ");
      tmp.push_back("\n");
      raw_.insert(raw_.end(), tmp.begin(), tmp.end());
    }
  }

  void tokenize() {
    tokens_.reserve(raw_.size());
    for (vector<string>::iterator it = raw_.begin(); it != raw_.end(); ++it) {
      Token token = {token_t::kUnset, *it};

      if (*it == "{")
        token.type = token_t::kLeftBracket;
      else if (*it == "}")
        token.type = token_t::kRightBracket;
      else if (*it == ";" || *it == "\n")
        token.type = token_t::kTerminator;
      else
        token.type = token_t::kWord;
      tokens_.push_back(token);
    }
  }

 public:
  // Constructors
  Tokenizer(std::ifstream& infile) : infile_(infile) {
    read_raw();
    tokenize();
  }

  // Getters
  vector<string> raw_data() const { return raw_; }
  vector<Token> tokens() const { return tokens_; }
  // Methods
};

std::ostream& operator<<(std::ostream& os, const Token& token) {
  os << "type: " << token_t::n[token.type] << ", value: '" << token.value
     << "'";
  return os;
}

}  // namespace util

#endif  // PARSER_TOKENIZER_HPP
