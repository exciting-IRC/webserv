#include <exception>
#include <fstream>
#include <iostream>
#include <logger/logger.hpp>
#include <logger/message.hpp>
#include <string>
#include <strutil/strutil.hpp>
#include <unordered_map>
#include <util/prettyprint.hpp>
#include <util/types.hpp>
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

i32 main() {
  using namespace logger;
  vector<token> tokens;
  // unordered_map<string, string> tokens;
  // tokens["{"] = "BracketBegin";
  // tokens["}"] = "BracketEnd";

  std::ifstream infile("config.conf");
  string line;
  for (i32 i = 0; std::getline(infile, line); i++) {
    strutil::erase_from(line, "#");

    vector<string> tokens = strutil::split(line);
    std::cout << Message("line", color_t::HiYellow).cyan(i) << std::endl;
    // prettyprint::simple(tokens);
    prettyprint::table(tokens);
  }

  return 0;
}
