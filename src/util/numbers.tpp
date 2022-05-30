#ifndef UTIL_NUMBERS_TPP
#define UTIL_NUMBERS_TPP

#include <sstream>
#include <util/numbers.hpp>

template <typename T>
size_t printed_width(const T& v) {
  std::stringstream ss;

  ss << v;
  return ss.str().length();
}

template <typename T>
const T& clamp(const T& v, const T& lo, const T& hi) {
  return std::min(std::max(v, lo), hi);
}

#endif  // UTIL_NUMBERS_TPP
