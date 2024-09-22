#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "NonCopyable.hh"

class Socket : public NonCopyable{
public:
    Socket();
    Socket(int fd);
    ~Socket();

    int getFd();

private:
    int fd_;
};

#endif

