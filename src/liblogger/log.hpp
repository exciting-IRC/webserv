#ifndef LIBLOGGER_LOG_HPP
#define LIBLOGGER_LOG_HPP

#include <iostream>
#include <liblogger/log.hpp>
#include <libutil/color.hpp>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace logger {

using std::string;

/**
 * @brief Colored text interface.
 *
 */
class Message {
 private:
  std::stringstream stream_;
  // typedef std::pair<string, string> coloredText;
  // std::vector<coloredText> data_;

 public:
  // Constructors & Destructor
  Message();
  ~Message();

  const string str() const { return stream_.str() + "\n"; }

  template <typename T>
  Message& withcolor(const T& msg, const string& color);

  template <typename T>
  Message& red(const T& msg);

  template <typename T>
  Message& green(const T& msg);

  template <typename T>
  Message& yellow(const T& msg);

  template <typename T>
  Message& magenta(const T& msg);

  template <typename T>
  Message& cyan(const T& msg);

  template <typename T>
  Message& add(const T& msg);

  Message& nl() {
    stream_ << "\n";
    return *this;
  }
};

std::ostream& operator<<(std::ostream& os, const Message& msg);

}  // namespace logger

#include <liblogger/log.tpp>

#endif  // LIBLOGGER_LOG_HPP
