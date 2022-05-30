#ifndef LOGGER_LOGGER_HPP
#define LOGGER_LOGGER_HPP

#include <fstream>
#include <iostream>
#include <logger/message.hpp>
#include <stdexcept>
#include <string>
#include <util/color.hpp>
namespace util {
using std::string;

class Logger {
 public:
  struct loglevel_t {
    enum e {
      Unset = -2,
      None = -1,
      Debug,
      Info,
      Warning,
      Error,
      Critical,
      LoglevelSize
    };
  };

  struct writeflag_t {
    enum e { None = 1 << 0, Newline = 1 << 1 };
  };

  typedef void (Logger::*logfunc)(const Message& msg);

 private:
  std::ofstream ofs_;
  // TODO: 출력 설정 벡터로 변경하기?
  loglevel_t::e stdout_loglevel_;
  loglevel_t::e file_loglevel_;

  void log(const Message& msg, const loglevel_t::e level);

 public:
  Logger();
  Logger(const string& logfile,
         loglevel_t::e stdout_loglevel = loglevel_t::Info,
         loglevel_t::e file_loglevel = loglevel_t::Debug);

  // Getters/Setters
  void set_loglevel(loglevel_t::e stdout_loglevel = loglevel_t::Unset,
                    loglevel_t::e file_loglevel = loglevel_t::Unset);

  // Methods
  void debug(const Message& msg);
  void info(const Message& msg);
  void warning(const Message& msg);
  void error(const Message& msg);
  void critical(const Message& msg);
};

}  // namespace util

#endif  // LOGGER_LOGGER_HPP
