#include <strutil/strutil.hpp>

namespace util {

string multiply(const string& s, size_t n) {
  std::ostringstream oss;

  for (size_t i = 0; i < n; i++) {
    oss << s;
  }
  return oss.str();
}

string center(const string& s, size_t width, char c) {
  if (s.size() >= width)
    return s;

  const size_t left = (width - s.length()) / 2;
  const size_t right = width - left - s.length();

  return string(left, c) + s + string(right, c);
}

string ljust(const string& s, size_t width, char c) {
  if (s.size() >= width)
    return s;

  return s + string(width - s.length(), c);
}

string rjust(const string& s, size_t width, char c) {
  if (s.size() >= width)
    return s;

  return string(width - s.length(), c) + s;
}

}  // namespace util
