#include <exception>
#include <fstream>
#include <iostream>
#include <logger/logger.hpp>
#include <logger/message.hpp>
#include <main/main.hpp>
#include <string>
#include <strutil/strutil.hpp>
#include <util/types.hpp>
#include <vector>

using std::string;
using std::vector;

int main() {
  logger::Message msg;
  logger::Logger logger;

  msg  //
      .add("Hello")
      .red("World!")
      .nl()
      .green("numbers are ok")
      .add(123)
      .yellow("even float:")
      .add(1.23);

  std::cout << msg;
  msg  //
      .nl()
      .add("You can also use colors like this.", color_t::BHYEL);

  std::cout << msg;
  std::cout << msg.plaintext(logger::flag_t::NEWLINE);

  logger.info(msg);

  try {
    std::cout << "invalid code:" << color::codes.at(12412124) << "\n";
  } catch (const std::exception& e) {
    std::cout << e.what() << "\n";
  }
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
