#ifndef STRUTIL_STRUTIL_HPP
#define STRUTIL_STRUTIL_HPP

#include <iostream>
#include <string>
#include <vector>

namespace strutil {

enum { MAXSPLIT_ALL = -1 };

using std::string;
using std::vector;

vector<string> split(const string& str, const string& sep = "");

template <typename T>
void print_vector(vector<T> v, bool oneline = true) {
  const string sep = oneline ? ", " : "\n";
  for (typename vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << "'" << *it << "'" << sep;
  }
  std::cout << "\n";
}

}  // namespace strutil

#endif  // STRUTIL_STRUTIL_HPP
