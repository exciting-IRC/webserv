#ifndef UTIL_PRETTYPRINT_HPP
#define UTIL_PRETTYPRINT_HPP

#include <algorithm>
#include <sstream>
#include <util/color.hpp>
#include <util/numbers.hpp>

namespace prettyprint {
using namespace color_str;

/// 컨테이너의 원소를 간결하게 출력
template <typename C>
void simple(const C& c, bool oneline = true) {
  const char* sep = oneline ? ", " : "\n";
  for (typename C::const_iterator it = c.begin(); it != c.end(); ++it) {
    std::cout << HRED << "'" << HCYN << *it << HRED << "'" << END << sep;
  }
  std::cout << "\n";
}

// struct string_tag {};

// struct unknown_tag {};

// template <typename T>
// struct is_string : unknown_tag {};

// template <>
// struct is_string<std::string> : string_tag {};

// namespace detail {
// template <typename C>
// void table_impl(const C& c, string_tag) {}

// void table_impl(const C& c, unknown_tag) {}

// }

// template <typename C>
// void table(const C& c) {
//   detail::table_impl(c, is_string<typename C::value_type>());
// }
// a < b
template <typename T>
static bool element_comp(const T& a, const T& b) {
  return printed_width(a) < printed_width(b);
}

template <typename C>
static const typename C::value_type& widest_element(const C& c) {
  if (c.size() == 0)
    throw std::runtime_error("empty container");

  return *std::max_element(c.begin(), c.end(),
                           element_comp<typename C::value_type>);
}

/// 컨테이너의 원소를 표로 출력
template <typename C>
void table(const C& c) {
  const u32 index_width = printed_width(c.size() - 1);
  const u32 elem_width = printed_width(widest_element(c));

  std::cout << "index_width: " << index_width << std::endl;
  std::cout << "elem_width: " << elem_width << std::endl;

  for (u32 i = 0; i < c.size(); i++) {
    std::cout << HRED << std::setw(index_width) << i << END << ": ";
    std::cout << HCYN << std::left << std::setw(elem_width) << c[i] << END
              << "\n";
  }

  // "─│╭╮╯╰"
  // printf "╭───┬──────╮\n│   │      │\n╰───┴──────╯\n"
}

}  // namespace prettyprint

#endif  // UTIL_PRETTYPRINT_HPP
