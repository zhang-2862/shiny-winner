#include "Acceptor.hh"


Acceptor::Acceptor(const string& ip, unsigned short port)
    : sock_(),
      addr_(ip, port)
{

} 

Acceptor::~Acceptor() {

} 

void Acceptor::ready() {
   setReuseAddr();
   setReusePort();
   bind();
   listen();
}

int Acceptor::accept() {
    return ::accept(sock_.getFd(), nullptr, nullptr);
}

void Acceptor::setReuseAddr() {
    int opt = 1;
    int ret = setsockopt(sock_.getFd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (ret == -1) {
        perror("setReuseAddr error");
        return;
    }
}

void Acceptor::setReusePort() {
    int opt = 1;
    int ret = setsockopt(sock_.getFd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (ret == -1) {
        perror("setReuseAddr error");
        return;
    }
}

void Acceptor::bind() {
    int ret = ::bind(sock_.getFd(), (struct sockaddr*)addr_.getInetAddressPtr(),
                     sizeof(struct sockaddr));
    if (ret == -1) {
        perror("bind error");
        return;
    }
}

void Acceptor::listen() {
    int ret = ::listen(sock_.getFd(), 128);
    if (ret == -1) {
        perror("listen error");
        return;
    }
}

// 提供获取listenfd的接口供EventLoop类使用
int Acceptor::fd() {
    return sock_.getFd();
}
