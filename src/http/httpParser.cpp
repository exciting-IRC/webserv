#include <unistd.h>

#include <string>

struct state {
  enum {
    kStart,
    kMethod,
    kSPAfterMethod,
    kSchema,
    kSlashAfterSchema,
    kSlashSlashAfterSchema,
    kHostStart,
    kHostName,
    kHostIp,
    kHostEnd,
    kPort,
    kURI,
    kLiteralH,
    kLiteralHT,
    kLiteralHTT,
    kLiteralHTTP,
    kLiteralHTTPSlash,
    kHttpVersionMajor,
    kHttpVersionDot,
    kHttpVersionMinor,
    kCR,
    kLF
  };
};

struct HttpRequest {
  enum Method { GET, HEAD, POST, DELETE };

  struct Version {
    int major;
    int minor;
  };

  struct Uri {
    std::string path;
    std::string schema;
    std::string port;
    std::string host;
    // query
  };
  // methods
};

#define DEFAULT_BUFFER_SIZE (1 << 16)  // 64KB

template <std::size_t buffer_size>
class FixedBuffer {
 public:
  FixedBuffer() : start_ptr_(new char[buffer_size]) {}
  ~FixedBuffer() { delete[] start_ptr_; }

 private:
  void copyBuffer(const FixedBuffer &other) {
    std::copy(other.begin(), other.end(), begin());
    end_ptr_ = start_ptr_ + std::distance(other.begin(), other.end());
  }

 public:
  FixedBuffer &operator=(const FixedBuffer &other) {
    copyBuffer(other);
    return *this;
  }

  FixedBuffer(const FixedBuffer &other) : start_ptr_(new char[buffer_size]) {
    copyBuffer(other);
  }

  operator[](std::size_t i) { return data_[i]; }
  std::size_t capacity() { return buffer_size; }

  char *end() { return end_ptr_; }
  char *begin() { return start_ptr_; }

 private:
  char *start_ptr_;
  char *end_ptr_;
  char data_[buffer_size];
  std::size_t cursor_;
};

#include <sys/socket.h>

class Client {
 public:
  ssize_t recv(std::size_t length, int flag);

 private:
  int sock_;
  FixedBuffer<DEFAULT_BUFFER_SIZE> buffer_;
  std::size_t tokenStart_;
  std::size_t tokenEnd_;
};

ssize_t Client::recv(std::size_t length, int flag = 0) {
  return ::recv(sock_, buffer_.end(), length, flag);
}
// std::Array

// ssize_t Client::recv

class HttpParserBase {
 public:
  char peek();
  char pop();
  void markTokenStart();
  void markTokenEnd();
  std::string getToken();

 private:
  Client &client;
};

class HttpParser : public HttpParserBase {};