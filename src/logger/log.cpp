#include <algorithm>
#include <iostream>
#include <logger/log.hpp>
#include <numeric>
#include <sstream>

namespace logger {

// Constructors & Destructor
Message::Message() {}
Message::~Message() {}

Message& Message::nl() {
  data_.push_back(coloredText("\n", color_t::NIL));
  return *this;
}

// Getters
const string Message::str() const {
  using color::is_colored;

  std::stringstream ss;
  color_t::impl now_color, prev_color = color_t::NIL;

  for (color_it it = data_.begin(); it != data_.end(); ++it) {
    now_color = it->second;
    if (is_colored(now_color))
      ss << color::codes.at(now_color);
    else if (is_colored(prev_color))
      ss << color::END;

    ss << it->first;
    prev_color = now_color;
  }
  ss << color::END << "\n";
  return ss.str();
}

const string Message::plaintext() const {
  std::stringstream ss;

  for (color_it it = data_.begin(); it != data_.end(); ++it)
    ss << it->first;
  ss << "\n";
  return ss.str();
}

// Overloaded << operator
std::ostream& operator<<(std::ostream& os, const Message& msg) {
  os << msg.str();
  return os;
}

}  // namespace logger
