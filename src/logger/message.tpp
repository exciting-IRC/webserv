#ifndef LOGGER_LOG_TPP
#define LOGGER_LOG_TPP

#include <logger/message.hpp>
#include <strutil/strutil.hpp>
#include <util/color.hpp>

namespace util {

template <typename T>
Message& Message::red(const T& msg) {
  return add(msg, color_t::Red);
}

template <typename T>
Message& Message::green(const T& msg) {
  return add(msg, color_t::Green);
}

template <typename T>
Message& Message::yellow(const T& msg) {
  return add(msg, color_t::HiYellow);
}

template <typename T>
Message& Message::magenta(const T& msg) {
  return add(msg, color_t::HiMagenta);
}

template <typename T>
Message& Message::cyan(const T& msg) {
  return add(msg, color_t::HiCyan);
}

template <typename T>
Message& Message::add(const T& msg, const color_t::e color) {
  data_.push_back(coloredText(util::to_string(msg) + " ", color));
  return *this;
}

}  // namespace util

#endif  // LOGGER_LOG_TPP
