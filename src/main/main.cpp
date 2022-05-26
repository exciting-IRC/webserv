#include <fstream>
#include <iostream>
#include <liblogger/log.hpp>
#include <libstrutil/strutil.hpp>
#include <libutil/types.hpp>
#include <main/main.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;

int main() {
  logger::Message msg;

  msg  //
      .add("Hello")
      .red("World!")
      .nl()
      .green("numbers are ok")
      .add(123);

  std::cout << msg;
  msg  //
      .nl()
      .add("You can also use colors like this:")
      .withcolor("cyan", color::HCYN);

  std::cout << msg.str();

// [12:00:03] addf added [asdsfa] to adsdfsff

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
