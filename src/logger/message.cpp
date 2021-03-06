#include <algorithm>
#include <iostream>
#include <logger/message.hpp>
#include <numeric>
#include <sstream>

namespace util {
// Getters
const string Message::str(flag_t::e flag) const {
  using color::is_colored;

  std::stringstream ss;
  color_t::e now_color, prev_color = color_t::NIL;

  for (color_it it = data_.begin(); it != data_.end(); ++it) {
    now_color = it->second;
    if (is_colored(now_color))
      ss << color::codes.at(now_color);
    else if (is_colored(prev_color))
      ss << color::END;

    ss << it->first;
    prev_color = now_color;
  }
  ss << color::END;
  if (flag == flag_t::NEWLINE)
    ss << "\n";
  return ss.str();
}

const string Message::plaintext(flag_t::e flag) const {
  std::stringstream ss;

  for (color_it it = data_.begin(); it != data_.end(); ++it)
    ss << it->first;
  if (flag == flag_t::NEWLINE)
    ss << "\n";
  return ss.str();
}

// Methods
Message& Message::nl() {
  data_.push_back(coloredText("\n", color_t::NIL));
  return *this;
}

// Overloaded << operator
std::ostream& operator<<(std::ostream& os, const Message& msg) {
  os << msg.str();
  return os;
}

}  // namespace util
