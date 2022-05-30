#ifndef STRUTIL_STRUTIL_TPP
#define STRUTIL_STRUTIL_TPP

#include <strutil/strutil.hpp>

namespace util {

template <typename T>
string to_string(const T& t) {
  std::stringstream ss;

  ss << t;
  return ss.str();
}

}  // namespace util

#endif  // STRUTIL_FORMAT_TPP
