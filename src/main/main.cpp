#include <exception>
#include <fstream>
#include <iostream>
#include <logger/logger.hpp>
#include <logger/message.hpp>
#include <map>
#include <prettyprint/prettyprint.hpp>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using std::map;
using std::pair;
using std::queue;
using std::string;
using std::vector;

// struct Tokens {
//   private:

//    public:

// };

// class tokenizer {
//   private:
//   public:
// };
// struct tokentype_t {
//   enum e { BracketBegin, BracketEnd };
// };

// struct token {
//   string type;
//   // tokentype_t::e type;
//   string value;
// };

// map<string, tokentype_t::> init_token_types() {
//   map<string, string> token_types;
//   token_types["{"] = "BracketBegin";
//   token_types["}"] = "BracketEnd";
//   token_types["server"] = "Server";
//   token_types["port"] = "Port";
//   token_types["server_names"] = "ServerNames";
//   token_types["username"] = "Username";
//   token_types["password"] = "Password";

//   return token_types;
// }

// string get_token_type(const string& s) {
//   static map<string, string> token_types = init_token_types();

//   return token_types[s];
// }
typedef vector<string> tokens_t;

tokens_t get_tokens(std::ifstream& infile) {
  using namespace util;

  string line;
  tokens_t tokens;

  for (int i = 0; std::getline(infile, line); i++) {
    util::erase_from(line, "#");
    if (line.empty())
      continue;

    vector<string> t = util::split(line);

    tokens.reserve(tokens.size() + t.size() + 1);
    for (vector<string>::iterator it = t.begin(); it != t.end(); ++it)
      tokens.push_back(*it);
    tokens.push_back("\n");
  }

  return tokens;
}

int main() {
  std::ifstream infile("config.conf");

  tokens_t tokens = get_tokens(infile);
  util::as_table(tokens);

  // std::ifstream infile("/Users/youkim/Repo/webserv/config.conf");
  // string line;
  // for (int i = 0; std::getline(infile, line); i++) {
  //   util::erase_from(line, "#");

  //   vector<string> tokens = util::split(line);
  //   std::cout << "line " << i << std::endl;
  //   util::print_vector(tokens);
  // }

  return 0;
}
