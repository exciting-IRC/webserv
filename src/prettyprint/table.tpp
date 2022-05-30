#ifndef PRETTYPRINT_TABLE_TPP
#define PRETTYPRINT_TABLE_TPP

#include <algorithm>
#include <prettyprint/table.hpp>
#include <sstream>
#include <strutil/strutil.hpp>
#include <util/color.hpp>
#include <util/comptime.hpp>
#include <util/numbers.hpp>
#include <vector>

namespace util {

// Getters

size_t table::row_width(size_t i) const { return column_widths[i] + 2; }

table::row_text_t table::row_box_text(const border_type_t::e type) const {
  const size_t at = 2 + type * 3;

  row_text_t result = {box_text[at], box_text[at + 1], box_text[at + 2]};
  return result;
}

// Methods

string table::border(const border_type_t::e type) const {
  using util::multiply;

  std::stringstream ss;
  row_text_t text = row_box_text(type);
  const string& l = box_text[box_text_t::Horizontal];

  ss << text.left;
  if (columns() > 0) {
    for (size_t i = 0; i < columns() - 1; i++)
      ss << multiply(l, row_width(i)) << text.mid;
    ss << multiply(l, column_widths.back() + 2);
  }
  ss << text.right;

  return ss.str();
}

string table::line(const row_t& row, bool is_header, bool center_after) const {
  using namespace util;

  std::stringstream ss;
  const string& cross = box_text[box_text_t::Vertical];
  const row_t& colors = is_header ? header_colors : row_colors;

  ss << cross;
  if (columns() > 0) {
    for (size_t i = 0; i < columns(); i++) {
      justify_func format = (i == 0 || center_after) ? center : ljust;

      ss << colors[i] << ' '
         << format((i < row.size()) ? replace(row[i], "\n", "\\n") : "",
                   row_width(i) - 1, ' ')
         << END;
      if (i < columns() - 1)
        ss << cross;
    }
  }
  ss << cross;
  return ss.str();
}

}  // namespace util

#endif  // PRETTYPRINT_TABLE_TPP
