#include <logger/log.hpp>

namespace logger {

// Constructors & Destructor
Message::Message() {}
Message::~Message() {}

Message& Message::nl() {
  data_.push_back(coloredText("\n", color_t::NIL));
  return *this;
}

// Overloaded << operator
std::ostream& operator<<(std::ostream& os, const Message& msg) {
  os << msg.str();
  return os;
}

}  // namespace logger
