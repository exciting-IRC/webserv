#include <fstream>
#include <iostream>
#include <logger/log.hpp>
#include <main/main.hpp>
#include <string>
#include <strutil/strutil.hpp>
#include <util/types.hpp>
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
      .withcolor("You can also use colors like this:", color::BHYEL)
      .withcolor("or use map", color::codes[color_t::HCYN]);

  std::cout << msg.str();

  std::cout << "invalid code:" << color::codes.at(12412124) << "\n";
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
