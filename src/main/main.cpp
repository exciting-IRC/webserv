#include <exception>
#include <fstream>
#include <iostream>
#include <logger/logger.hpp>
#include <logger/message.hpp>
#include <string>
#include <unordered_map>
#include <util/prettyprint.hpp>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

// struct Tokens {
//   private:

//    public:

// };

// class tokenizer {
//   private:
//   public:
// };
struct tokentype_t {
  enum e { BracketBegin, BracketEnd };
};

struct token {
  tokentype_t::e type;
  string value;
};

int main() {
  using namespace util;
  vector<token> tokens;
  // unordered_map<string, string> tokens;
  // tokens["{"] = "BracketBegin";
  // tokens["}"] = "BracketEnd";

  std::ifstream infile("config.conf");
  string line;
  for (int i = 0; std::getline(infile, line); i++) {
    util::erase_from(line, "#");

    vector<string> tokens = util::split(line);
    std::cout << Message("line", color_t::HiYellow).cyan(i) << std::endl;
    // prettyprint::simple(tokens);
    prettyprint::table(tokens);
  }
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
