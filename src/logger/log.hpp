#ifndef LOGGER_LOG_HPP
#define LOGGER_LOG_HPP

#include <string>
#include <util/color.hpp>
#include <utility>
#include <vector>

namespace logger {

using std::string;
using std::vector;
/**
 * @brief Colored text interface.
 *
 */
class Message {
 private:
  // std::stringstream stream_;
  typedef std::pair<string, color_t::impl> coloredText;
  typedef std::vector<coloredText>::const_iterator color_it;
  vector<coloredText> data_;

 public:
  // Constructors & Destructor
  Message();
  ~Message();

  // Getters
  const string str() const;
  const string plaintext() const;

  // Methods
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
  Message& add(const T& msg, const color_t::impl color = color_t::NIL);

  Message& nl();
};

// Overloaded << operator
std::ostream& operator<<(std::ostream& os, const Message& msg);

}  // namespace logger

#include <logger/log.tpp>

#endif  // LOGGER_LOG_HPP
