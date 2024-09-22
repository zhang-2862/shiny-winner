#include "Socket.hh"

#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

Socket::Socket() {
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0) {
        perror("socket error");
    }
}

Socket::Socket(int fd)
    : fd_(fd)
{

}

Socket::~Socket() {
    close(fd_);
}

int Socket::getFd() {
    return fd_;
}

