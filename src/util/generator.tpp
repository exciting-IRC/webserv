#ifndef UTIL_GENERATOR_TPP
#define UTIL_GENERATOR_TPP

#include <util/generator.hpp>

namespace util {

template <typename Iter>
Iter choice(Iter begin, Iter end) {
  return begin + (u_random() % std::distance(begin, end));
}

template <typename T>
T gen(int min, int max) {
  return u_random() % (max - min) + min;
}

template <typename T>
T gen(int max) {
  return gen<T>(0, max);
}

}  // namespace util

#endif // UTIL_GENERATOR_TPP
