#ifndef PRETTYPRINT_PRETTYPRINT_HPP
#define PRETTYPRINT_PRETTYPRINT_HPP

#include <algorithm>
#include <prettyprint/table.hpp>
#include <sstream>
#include <strutil/strutil.hpp>
#include <util/color.hpp>
#include <util/comptime.hpp>
#include <util/numbers.hpp>
#include <vector>

namespace util {
using namespace color_str;

/// 컨테이너의 원소를 간결하게 출력
template <typename C>
void simple(const C& c, bool oneline = true);

template <typename C>
const typename C::value_type& widest_element(const C& c);

template <typename C>
void as_table(const C& c, bool is_print_heading = true);

}  // namespace util

#include <prettyprint/prettyprint.tpp>

#endif  // UTIL_PRETTYPRINT_HPP
