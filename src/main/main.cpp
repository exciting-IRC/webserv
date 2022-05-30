#include <iostream>
#include <parser/tokenizer.hpp>
#include <prettyprint/prettyprint.hpp>
#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

struct RawServer {
  string server_name;
  string listen;
};

struct BraceCounter {
  int left, right;
};

int main() {
  using namespace util;
  std::ifstream infile("config/brace_unmatch.conf");

  Tokenizer tokenizer(infile);
  vector<Token> tokens = tokenizer.tokens();
  util::as_table(tokens);
  // tokens_t tokens = util::tokenize(infile);

  // if (tokens.empty()) {
  //   std::cout << "No tokens found" << std::endl;
  //   return 0;
  // }

  // util::as_table(tokens);

  return 0;
}
