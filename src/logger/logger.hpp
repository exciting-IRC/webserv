#ifndef LOGGER_LOGGER_HPP
#define LOGGER_LOGGER_HPP

#include <fstream>
#include <iostream>
#include <logger/message.hpp>
#include <stdexcept>
#include <string>
#include <util/color.hpp>
namespace logger {
using std::string;

// TODO: cpp로 변경하기
class Logger {
 public:
  struct loglevel_t {
    enum impl {
      UNSET = -2,
      NONE = -1,
      DEBUG,
      INFO,
      WARNING,
      ERROR,
      CRITICAL,
      LOGLEVEL_SIZE
    };
  };

  struct writeflag_t {
    enum impl { NONE = 1 << 0, NEWLINE = 1 << 1 };
  };

  typedef void (Logger::*logfunc)(const Message& msg);

 private:
  std::ofstream ofs;
  // TODO: 출력 설정 벡터로 변경하기?
  loglevel_t::impl stdout_loglevel_;
  loglevel_t::impl file_loglevel_;

  // void log(const Message& msg, const loglevel_t::impl level);
  void log(const Message& msg, const loglevel_t::impl level) {
    const Message levelMessages[] = {
        Message("DEBUG:    ", color_t::HBLU),
        Message("INFO:     ", color_t::HGRN),
        Message("WARNING:  ", color_t::BHYEL),
        Message("ERROR:    ", color_t::RED),
        Message("CRITICAL: ", color_t::BHRED),
    };

    if (level >= loglevel_t::LOGLEVEL_SIZE) {
      throw std::out_of_range(
          Message("level").red(level).add("is out of range").str());
    }
    if (level >= file_loglevel_)
      ofs << levelMessages[level].plaintext() << msg.plaintext(flag_t::NEWLINE);
    if (level >= stdout_loglevel_)
      std::cout << levelMessages[level] << msg.str(flag_t::NEWLINE);
  }

 public:
  Logger()
      : stdout_loglevel_(loglevel_t::DEBUG), file_loglevel_(loglevel_t::NONE) {}
  Logger(const string& logfile,
         loglevel_t::impl stdout_loglevel = loglevel_t::INFO,
         loglevel_t::impl file_loglevel = loglevel_t::DEBUG)
      // Logger(const string& logfile, loglevel_t::impl file_loglevel,
      //        loglevel_t::impl stdout_loglevel)
      : stdout_loglevel_(stdout_loglevel), file_loglevel_(file_loglevel) {
    ofs.open(logfile.c_str(), std::fstream::out | std::fstream::app);
  }

  // Getters/Setters
  void set_loglevel(loglevel_t::impl stdout_loglevel = loglevel_t::UNSET,
                    loglevel_t::impl file_loglevel = loglevel_t::UNSET) {
    bool out, file;
    if ((out = (stdout_loglevel != loglevel_t::UNSET))) {
      stdout_loglevel_ = stdout_loglevel;
      debug(Message("set stdout_loglevel_ to").cyan(stdout_loglevel_));
    }
    if ((file = (file_loglevel != loglevel_t::UNSET))) {
      file_loglevel_ = file_loglevel;
      debug(Message("set file_loglevel_ to").cyan(file_loglevel_));
    }
    if (!out && !file)
      throw std::invalid_argument("loglevels cannot be both unset");
  }

  // void info(const Message& msg);
  // void warning(const Message& msg);
  // void error(const Message& msg);
  // void debug(const Message& msg);

  // Methods
  void debug(const Message& msg) { log(msg, loglevel_t::DEBUG); }
  void info(const Message& msg) { log(msg, loglevel_t::INFO); }
  void warning(const Message& msg) { log(msg, loglevel_t::WARNING); }
  void error(const Message& msg) { log(msg, loglevel_t::ERROR); }
  void critical(const Message& msg) { log(msg, loglevel_t::CRITICAL); }
};

}  // namespace logger

#endif  // LOGGER_LOGGER_HPP
