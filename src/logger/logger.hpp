#ifndef LOGGER_LOGGER_HPP
#define LOGGER_LOGGER_HPP

#include <iostream>
#include <logger/message.hpp>
#include <util/color.hpp>
namespace logger {
class Logger {
 private:
 public:
  void info(const Message& msg) { std::cout << Message().add("INFO:     ", color_t::HGRN) << msg; }
  void debug() {}
  void warning() {}
};

}  // namespace logger

#endif  // LOGGER_LOGGER_HPP
