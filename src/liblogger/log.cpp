#include <liblogger/log.hpp>

namespace logger {

Message::Message() {}
Message::~Message() {}

std::ostream& operator<<(std::ostream& os, const Message& msg) {
  os << msg.str();
  return os;
}

}  // namespace logger
