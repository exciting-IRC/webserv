#ifndef STRUTIL_STRUTIL_HPP
#define STRUTIL_STRUTIL_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace util {

using std::string;
using std::vector;

enum { MAXSPLIT_ALL = -1 };

extern const string white_space;

string& erase_from(string& line, const string& match);
string& ltrim(string& s, const string& match = white_space);
string& rtrim(string& s, const string& match = white_space);
string& trim(string& s, const string& match = white_space);

string center(const string& s, size_t width, char c = ' ');
string ljust(const string& s, size_t width, char c = ' ');
string rjust(const string& s, size_t width, char c = ' ');

typedef string& (*trim_func)(string& s, const string& match);
typedef string (*justify_func)(const string& s, size_t width, char c);

string multiply(const string& s, size_t n);
string replace(string s, const string& old_value, const string& new_value);

vector<string> split(const string& str, const string& sep = "");

template <typename T>
string to_string(const T& t);
}  // namespace util

#include <strutil/strutil.tpp>

#endif  // STRUTIL_STRUTIL_HPP
