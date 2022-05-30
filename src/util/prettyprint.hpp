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

string multiply(const string& s, size_t n) {
  std::ostringstream oss;

  for (size_t i = 0; i < n; i++) {
    oss << s;
  }
  return oss.str();
}

string center(const string& s, size_t width) {
  const size_t left = (width - s.length()) / 2;
  const size_t right = width - left - s.length();

  return string(left, ' ') + s + string(right, ' ');
}

/// 컨테이너의 원소를 표로 출력
template <typename C>
void table(const C& c, bool is_print_heading = true) {
  const size_t index_width = printed_width(c.size());
  const size_t elem_width =
      clamp<size_t>(printed_width(widest_element(c)), 10u, 80u);

  std::cout << "╭" << multiply("─", index_width + 2) << "┬"
            << multiply("─", elem_width + 2) << "╮\n";

  if (is_print_heading) {
    std::cout << "│ " << HYEL << std::setw(index_width) << "#" << END << " │"
              << HGRN << center("data", elem_width + 1) << END << " │\n";

    std::cout << "├" << multiply("─", index_width + 2) << "┼"
              << multiply("─", elem_width + 2) << "┤\n";
  }

  for (size_t i = 0; i < c.size(); i++) {
    std::cout << "│ " << HRED << std::setw(index_width) << i << END << " │ ";
    std::cout << (c[i].size() > 1 ? HCYN : "") << std::left
              << std::setw(elem_width) << c[i] << END << " │\n";
  }

  std::cout << "╰" << multiply("─", index_width + 2) << "┴"
            << multiply("─", elem_width + 2) << "╯\n";
}

}  // namespace prettyprint

#endif  // UTIL_PRETTYPRINT_HPP
