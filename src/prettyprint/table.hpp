#ifndef PRETTYPRINT_TABLE_HPP
#define PRETTYPRINT_TABLE_HPP

#include <algorithm>
#include <array>
#include <prettyprint/table.hpp>
#include <sstream>
#include <strutil/strutil.hpp>
#include <util/color.hpp>
#include <util/comptime.hpp>
#include <util/numbers.hpp>
#include <vector>

namespace util {
using namespace color_str;

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
  typedef std::array<string, columns> row_t;
  struct row_text_t {
    const string &left, &mid, &right;
  };

  const std::array<int, columns> column_widths;
  const row_t headers;

  const std::array<string, 11> box_text;
  const row_t header_colors;
  const row_t row_colors;

  // Getters
  size_t row_width(size_t i) const;
  row_text_t row_box_text(const border_type_t::e type) const;

  // Methods
  string border(const border_type_t::e type) const;
  string line(const row_t& row, bool is_header = false,
              bool center_after = false) const;

  string top() const { return border(border_type_t::Top); }
  string mid() const { return border(border_type_t::Mid); }
  string bottom() const { return border(border_type_t::Bottom); }
};
}  // namespace util

#include <prettyprint/table.tpp>

#endif  // PRETTYPRINT_TABLE_HPP
