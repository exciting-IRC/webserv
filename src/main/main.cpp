#include <fstream>
#include <iostream>
#include <libstrutil/strutil.hpp>
#include <libutil/types.hpp>
#include <main/main.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;

int main() {
  string s = "    hello  world    ";
  string sl(s), sr(s), st(s);

  std::cout << "[" << strutil::ltrim(sl) << "]\n";
  std::cout << "[" << strutil::rtrim(sr) << "]\n";
  std::cout << "[" << strutil::trim(st) << "]\n";

  string se = "", se2 = "      ";
  std::cout << "[" << strutil::trim(se) << "]\n";
  std::cout << "[" << strutil::trim(se2) << "]\n";
  // std::ifstream infile("/Users/youkim/Repo/webserv/config.conf");
  // string line;
  // for (i32 i = 0; std::getline(infile, line); i++) {
  //   strutil::erase_from(line, "#");

  //   vector<string> tokens = strutil::split(line);
  //   std::cout << "line " << i << std::endl;
  //   strutil::print_vector(tokens);
  // }

  return 0;
}
