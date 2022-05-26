#ifndef LIBLOGGER_LOG_TPP
#define LIBLOGGER_LOG_TPP

#include <liblogger/log.hpp>

namespace logger {

template <typename T>
Message& Message::withcolor(const T& msg, const string& color) {
  stream_ << color << msg << " " END;
  return *this;
}

template <typename T>
Message& Message::red(const T& msg) {
  return withcolor(msg, HRED);
}

template <typename T>
Message& Message::green(const T& msg) {
  return withcolor(msg, HGRN);
}

template <typename T>
Message& Message::yellow(const T& msg) {
  return withcolor(msg, HYEL);
}

template <typename T>
Message& Message::magenta(const T& msg) {
  return withcolor(msg, HMAG);
}

template <typename T>
Message& Message::cyan(const T& msg) {
  return withcolor(msg, HCYN);
}

template <typename T>
Message& Message::add(const T& msg) {
  stream_ << msg << " ";
  return *this;
}
}  // namespace logger

#endif  // LIBLOGGER_LOG_TPP
