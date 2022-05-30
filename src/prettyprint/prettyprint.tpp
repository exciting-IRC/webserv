#ifndef PRETTYPRINT_PRETTYPRINT_TPP
#define PRETTYPRINT_PRETTYPRINT_TPP

#include <prettyprint/prettyprint.hpp>

namespace util {

template <typename C>
void simple(const C& c, bool oneline) {
  const char* sep = oneline ? ", " : "\n";

  std::copy(c.begin(), c.end(),
            std::ostream_iterator<typename C::value_type>(std::cout, sep));
  std::cout << "\n";
}

template <typename T>
static bool element_comp(const T& a, const T& b) {
  return printed_width(a) < printed_width(b);
}

template <typename C>
const typename C::value_type& widest_element(const C& c) {
  if (c.size() == 0)
    throw std::runtime_error("empty container");

  return *std::max_element(c.begin(), c.end(),
                           element_comp<typename C::value_type>);
}

template <typename C>
void as_table(const C& c, bool is_print_heading) {
  const size_t index_width = printed_width(c.size());
  const size_t elem_width =
      clamp<size_t>(printed_width(widest_element(c)), 10u, 80u);

  std::array<int, 2> widths = {index_width, elem_width};
  std::array<string, 2> header = {"#", "data"};

  table<2> t = {widths, header, default_box_text, default_header_colors,
                default_row_colors};

  if (is_print_heading) {
    std::cout << t.top() << "\n"
              << t.line(t.headers, true) << "\n"
              << t.mid() << "\n";
  }
  for (size_t i = 0; i < c.size(); i++) {
    std::array<string, 2> row = {util::to_string(i), util::to_string(c[i])};
    std::cout << t.line(row) << "\n";
  }
  std::cout << t.bottom() << "\n";
}

}  // namespace util

#endif  // UTIL_PRETTYPRINT_TPP
