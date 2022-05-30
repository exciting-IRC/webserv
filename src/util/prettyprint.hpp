#ifndef UTIL_PRETTYPRINT_HPP
#define UTIL_PRETTYPRINT_HPP

#include <algorithm>
#include <array>
#include <sstream>
#include <strutil/strutil.hpp>
#include <util/color.hpp>
#include <util/comptime.hpp>
#include <util/numbers.hpp>
#include <vector>

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

string center(const string& s, size_t width, char c = ' ') {
  if (s.size() >= width)
    return s;

  const size_t left = (width - s.length()) / 2;
  const size_t right = width - left - s.length();

  return string(left, c) + s + string(right, c);
}

string ljust(const string& s, size_t width, char c = ' ') {
  if (s.size() >= width)
    return s;

  return s + string(width - s.length(), c);
}

string rjust(const string& s, size_t width, char c = ' ') {
  if (s.size() >= width)
    return s;

  return string(width - s.length(), c) + s;
}

typedef string (*format_func)(const string& s, size_t width, char c);

struct box_text_t {
  enum e {
    // clang-format off
    Horizontal, Vertical,
    TopLeft, TopMid, TopRight,
    LineLeft, LineMid, LineRight,
    BottomLeft, BottomMid, BottomRight
    // clang-format on
  };
};

struct border_type_t {
  enum e { Top, Mid, Bottom };
};

std::array<string, 2> default_header_colors = {HYEL, HGRN};
std::array<string, 2> default_row_colors = {HRED, HCYN};
std::array<string, 11> default_box_text = {"─", "│", "╭", "┬", "╮", "├",
                                           "┼", "┤", "╰", "┴", "╯"};

template <size_t columns>
struct table {
  std::array<int, columns> column_widths;
  std::array<string, columns> headers;

  std::array<string, 11> box_text;
  std::array<string, columns> header_colors;
  std::array<string, columns> row_colors;

  // Getters
  size_t row_width(size_t i) const { return column_widths[i] + 2; }
  // size_t columns() const { return column_widths.size(); }
  std::array<string, 3> row_box_text(const border_type_t::e type) const {
    const size_t at = 2 + type * 3;

    std::array<string, 3> result = {box_text[at], box_text[at + 1],
                                    box_text[at + 2]};
    return result;
  }

  // Methods
  string border(const border_type_t::e type) const {
    std::stringstream ss;
    std::array<string, 3> text = row_box_text(type);

    ss << text[0];
    if (columns > 0) {
      for (size_t i = 0; i < columns - 1; i++)
        ss << multiply("─", row_width(i)) << text[1];
      ss << multiply("─", column_widths.back() + 2);
    }
    ss << text[2];

    return ss.str();
  }

  string line(const std::array<string, columns>& row, bool is_header = false,
              bool center_after = false) const {
    const string& cross = box_text[box_text_t::Vertical];
    const std::array<string, columns>& colors =
        is_header ? header_colors : row_colors;
    std::stringstream ss;

    ss << cross;
    for (size_t i = 0; i < columns; i++) {
      format_func format = (i == 0 || center_after) ? center : ljust;
      ss << colors[i] << ' '
         << format((i < row.size()) ? row[i] : "", row_width(i) - 1, ' ')
         << END;
      if (i < columns - 1)
        ss << cross;
    }
    ss << cross;
    return ss.str();
  }

  string top() const { return border(border_type_t::Top); }
  string mid() const { return border(border_type_t::Mid); }
  string bottom() const { return border(border_type_t::Bottom); }

  void header() const {
    std::cout << top() << "\n" << line(headers, true) << "\n" << mid() << "\n";
  }
};

/// 컨테이너의 원소를 표로 출력
template <typename C>
void as_table(const C& c, bool is_print_heading = true) {
  const size_t index_width = printed_width(c.size());
  const size_t elem_width =
      clamp<size_t>(printed_width(widest_element(c)), 10u, 80u);

  std::array<int, 2> widths = {index_width, elem_width};
  std::array<string, 2> header = {"#", "data"};

  table<2> t = {widths, header, default_box_text, default_header_colors,
                default_row_colors};

  if (is_print_heading) {
    t.header();
  }
  for (size_t i = 0; i < c.size(); i++) {
    std::array<string, 2> row = {util::to_string(i), c[i]};
    std::cout << t.line(row) << "\n";
  }
  std::cout << t.bottom() << "\n";
}

}  // namespace prettyprint

#endif  // UTIL_PRETTYPRINT_HPP
