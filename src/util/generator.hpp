#ifndef UTIL_GENERATOR_HPP
#define UTIL_GENERATOR_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <string>

namespace util {
using std::string;

static struct random {
  size_t seed;

  random() : seed(time(NULL)) {}
  random(size_t seed) : seed(seed) {}

  size_t operator()() {
    seed = seed * 1103515245 + 12345;
    return (seed / 65536) % 32768;
  }
} u_random;

std::ostream &operator<<(std::ostream &os, const random &r);

template <typename Iter>
Iter choice(Iter begin, Iter end);

template <typename T>
T gen(int min, int max);

template <typename T>
T gen(int max = 10);

template <>
string gen(int min, int max);

}  // namespace util

#include <util/generator.tpp>

#endif  // UTIL_GENERATOR_HPP
