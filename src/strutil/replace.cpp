#include <algorithm>
#include <strutil/strutil.hpp>

namespace util {
string replace(string s, const string& old_value, const string& new_value) {
  size_t start_pos = 0;

  while ((start_pos = s.find(old_value, start_pos)) != std::string::npos) {
    s.replace(start_pos, old_value.length(), new_value);
    start_pos += new_value.length();  // Handles case where 'new_value' is a
                                      // substring of 'old_value'
  }
  return s;
}

}  // namespace util
