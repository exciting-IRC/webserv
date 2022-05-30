

#ifndef UTIL_NUMBERS_HPP
#define UTIL_NUMBERS_HPP

template <typename T>
size_t printed_width(const T& v);

template <typename T>
const T& clamp(const T& v, const T& lo, const T& hi);

#include <util/numbers.tpp>

#endif  // UTIL_NUMBERS_HPP
