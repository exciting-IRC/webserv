#include <cctype>
#include <cstring>
#include <algorithm>

namespace httpParser {

inline bool isAlpha(char c) {
  return std::isalpha(c);
}

inline bool isDigit(char c) {
  return std::isdigit(c);
}

inline bool isXDigit(char c) {
  return std::isxdigit(c);
}

inline bool isVCHAR(char c) {
  return std::isprint(c);
}


inline bool isHTAB(char c) {
  return c == '\t';
}

inline bool isSP(char c) {
  return c == ' ';
}

inline bool isCR(char c) {
  return c == '\r';
}

inline bool isLF(char c) {
  return c == '\n';
}

template <typename T>
bool isContained(char []) {

}

// c cannot be null charactor ('\0')
static inline bool isContained(const char *charset, char c) {
  std::lower_bound();
  return std::strchr(charset, c) != NULL;
}

inline bool isUnReserved(char c) {
  return isDigit(c) || isAlpha(c) || isContained(".~_-", c);
}

}  // namespace httpParser