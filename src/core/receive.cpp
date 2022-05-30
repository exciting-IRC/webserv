#include <arpa/inet.h>
#include <err.h>
#include <fcntl.h>
#include <sys/event.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

enum ExitStatus {
  kSuccess = 0,
  kInitKqueue,
  kInitSocket,
  kBindSocket,
  kListen,
  kFcntl,
  kKqueueCTL,
  kKqueueWait
  /*
  k,
  kExitSuccess,
  kExitSuccess,
  kExitSuccess,
  kExitSuccess,
  */
};

// int k = kevent();

inline int kevent_ctl(int kq, const struct kevent *changelist, int nchanges,
                      const struct timespec *timeout) {
  return kevent(kq, changelist, nchanges, NULL, 0, timeout);
}

inline int kevent_wait(int kq, struct kevent *eventlist, int nevents,
                       const struct timespec *timeout) {
  return kevent(kq, NULL, 0, eventlist, nevents, timeout);
}

// struct EWSConfigure {
//   ushort listenPort;
// };

// EWSConfigure conf;

// XXX hard coded configure

struct sockaddr_in addr;
void init_addr(struct sockaddr_in *addr) {
  memset(addr, 0x00, sizeof(*addr));
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr("127.0.0.1");
  addr->sin_port = htons(8112);
}

#define BACKLOG 64

#define _EV_SET(event, ident, filter, flags, fflags, data, udata) \
  EV_SET(event, ident, filter, flags, fflags, data, udata)

struct Client {
  Client() : sock(-1), buffer() {}
  int sock;
  std::string buffer;
};

// XXX vector<Client> client_ ?
template <int maxClient>
class ClientList {
 public:
  // XXX range based construct
  ClientList() {
    emptySpace_.reserve(maxClient);
    for (int i = 0; i < maxClient; ++i) {
      emptySpace_.push_back(clients_ + i);
    }
  }

  Client *add(int sock) {
    Client *cli = emptySpace_.back();
    emptySpace_.pop_back();
    cli->sock = sock;
    return cli;
  };

  void remove(Client *cli) {
    close(cli->sock);
    cli->buffer.clear();
    emptySpace_.push_back(cli);
  }

 private:
  typedef std::vector<Client *> ClientStack;

 private:
  Client clients_[maxClient];
  ClientStack emptySpace_;
};

#define GET_CLIENT(ptr) reinterpret_cast<Client *>(ptr);

typedef ClientList<BACKLOG> CList;

CList clients;

int serverSocket;
char buf[8096];
// XXX hard corded configure end

void graceful_exit(int) {
  close(serverSocket);
  exit(0);
}

int main() {
  signal(SIGINT, graceful_exit);
  init_addr(&addr);
  int kq = kqueue();

  if (kq == -1)
    err(kInitKqueue, "kqueue_init");

  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1)
    err(kInitSocket, "socket_init");

  if (fcntl(serverSocket, F_SETFD, O_NONBLOCK))
    err(kFcntl, "fcntl");

  if (bind(serverSocket, reinterpret_cast<const sockaddr *>(&addr),
           sizeof(addr)))
    err(kBindSocket, "bind");

  if (listen(serverSocket, BACKLOG))
    err(kListen, "listen");

  struct kevent ev;
  _EV_SET(&ev, serverSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
  if (kevent_ctl(kq, &ev, 1, NULL) == -1)
    err(kKqueueCTL, "kqueue_ctl");

  struct kevent evs[BACKLOG];
  while (true) {
    int nevents = kevent_wait(kq, evs, BACKLOG, NULL);
    if (nevents == -1)
      err(kKqueueWait, "kqueue_wait");
    if (nevents == 0)
      err(kKqueueWait, "timeout");
    // for (struct kevent *e = evs + BACKLOG - 1; e >= evs; --e) {
    for (int i = 0; i < BACKLOG; ++i) {
      struct kevent *e = &evs[i];
      Client *cli = GET_CLIENT(e->udata);
      if (e->filter == EVFILT_READ) {
        if (e->flags & EV_EOF) {
          clients.remove(cli);
          continue;
        }
        if (e->ident == serverSocket) {
          std::cout << "Accept connection" << std::endl;
          int sock = accept(serverSocket, NULL, NULL);
          if (sock == -1) {
            perror("accept");
            continue;
          }
          _EV_SET(&ev, sock, EVFILT_READ, EV_ADD, 0, 0, clients.add(sock));
          if (kevent_ctl(kq, &ev, 1, NULL) == -1) {
            perror("kevent_ctl(client)");
            continue;
          }
        } else {
          cli->buffer.reserve((std::size_t)e->data);
          std::cout << "len: " << e->data << std::endl;
          // XXX hmm....
          for (std::size_t i = e->data; i > 0;
               i -= std::min((std::size_t)8096, (std::size_t)e->data)) {
            recv(cli->sock, buf,
                 std::min((std::size_t)8096, (std::size_t)e->data), 0);

            cli->buffer.append(
                buf, std::min((std::size_t)8096, (std::size_t)e->data));
          }
          std::cout << cli->buffer << std::endl;
        }
      }
    }
  }
  return 0;
}