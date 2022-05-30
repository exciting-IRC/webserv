#include <iostream>
#include <parser/tokenize.hpp>
#include <prettyprint/prettyprint.hpp>
#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

int main() {
  using util::tokens_t;
  std::ifstream infile("config.conf");

  tokens_t tokens = util::tokenize(infile);
  util::as_table(tokens);

  return 0;
}
