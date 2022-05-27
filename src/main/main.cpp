#include <exception>
#include <fstream>
#include <iostream>
#include <logger/logger.hpp>
#include <logger/message.hpp>
#include <string>
#include <strutil/strutil.hpp>
#include <util/types.hpp>
#include <vector>

using std::string;
using std::vector;

int main() {

  // [12:00:03] addf added [asdsfa] to adsdfsff

  std::ifstream infile("/Users/youkim/Repo/webserv/config.conf");
  string line;
  for (i32 i = 0; std::getline(infile, line); i++) {
    strutil::erase_from(line, "#");

    vector<string> tokens = strutil::split(line);
    std::cout << "line " << i << std::endl;
    strutil::print_vector(tokens);
  }

  return 0;
}
