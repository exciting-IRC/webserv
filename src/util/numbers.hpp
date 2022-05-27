

#ifndef UTIL_NUMBERS_HPP
#define UTIL_NUMBERS_HPP

#include <util/types.hpp>

template <typename T>
u32 printed_width(const T& v);

template <typename T>
const T& clamp(const T& v, const T& lo, const T& hi);

#include <util/numbers.tpp>

#endif  // UTIL_NUMBERS_HPP
