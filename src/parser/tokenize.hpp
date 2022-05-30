#ifndef PARSER_TOKENIZE_HPP
#define PARSER_TOKENIZE_HPP

#include <fstream>
#include <string>
#include <strutil/strutil.hpp>
#include <vector>

namespace util {
using std::string;
using std::vector;

typedef vector<string> tokens_t;

tokens_t tokenize(std::ifstream& infile) {
  using namespace util;

  string line;
  tokens_t tokens;

  for (int i = 0; std::getline(infile, line); i++) {
    util::erase_from(line, "#");
    if (line.empty())
      continue;

    tokens_t t = util::split(line);
    t.push_back("\n");
    tokens.insert(tokens.end(), t.begin(), t.end());
  }

  return tokens;
}

}  // namespace util

#endif  // PARSER_TOKENIZE_HPP
