#include <cstdlib>
#include <string>
#include <strutil/strutil.hpp>
#include <util/generator.hpp>

namespace util {

using std::string;

std::ostream &operator<<(std::ostream &os, const random &r) {
  os << r.seed;
  return os;
}

template <>
string gen(int min, int max) {
  string s;
  const string candidate = util::alnums + util::whitespace;
  const int length = gen<int>(min, max);

  for (int i = 0; i < length; i++)
    s += *choice(candidate.begin(), candidate.end());
  return s;
}

}  // namespace util
