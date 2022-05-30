#include <exception>
#include <fstream>
#include <iostream>
#include <logger/logger.hpp>
#include <logger/message.hpp>
#include <main/main.hpp>
#include <string>
#include <strutil/strutil.hpp>
#include <util/generator.hpp>
#include <vector>

using std::string;
using std::vector;

int main() {
  using namespace util;

  for (int i = 0; i < 10; i++) {
    std::cout << gen<int>(-10, 10) << std::endl;
    std::cout << "'" << gen<string>(20) << "'" << std::endl;
  }
  // typedef Logger::loglevel_t loglevel_t;

  // Logger logger("test.log");

  // Message msgs[] = {"Hello World!"};
  // Logger::logfunc logfuncs[] = {&Logger::debug, &Logger::info,
  // &Logger::warning,
  //                               &Logger::error, &Logger::critical};

  // for (int loglevel = loglevel_t::DEBUG; loglevel <
  // loglevel_t::LOGLEVEL_SIZE;
  //      ++loglevel) {
  //   std::cout << "log level: " << loglevel << "\n";
  //   logger.set_loglevel((loglevel_t::e)loglevel);
  //   for (int i = 0; i < 5; i++) {
  //     (logger.*logfuncs[i])(msgs[0]);
  //   }
  // }

  // [12:00:03] addf added [asdsfa] to adsdfsff

  // std::ifstream infile("/Users/youkim/Repo/webserv/config.conf");
  // string line;
  // for (int i = 0; std::getline(infile, line); i++) {
  //   strutil::erase_from(line, "#");

  //   vector<string> tokens = util::split(line);
  //   std::cout << "line " << i << std::endl;
  //   util::print_vector(tokens);
  // }

  return 0;
}
