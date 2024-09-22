#include "TcpConnection.hh"
#include "EventLoop.hh"

#include <sstream>

TcpConnection::TcpConnection(int fd, EventLoop* loop) 
    : loop_(loop),
      sockIO_(fd),
      sock_(fd),
      localAddr_(getLocalAddr()),
      peerAddr_(getPeerAddr())
{

} 

TcpConnection::~TcpConnection() 
{

}

string TcpConnection::receive() {
    char buf[BUFSIZ];
    sockIO_.readLine(buf,BUFSIZ);
    return buf;
}

void TcpConnection::send(const string& msg) {
    sockIO_.writen(msg.c_str(), msg.size());
}

string TcpConnection::toString() {
    std::ostringstream oss;
    oss << localAddr_.getIp() << ":" << localAddr_.getPort()
        << "--->"
        << peerAddr_.getIp() << ":" << peerAddr_.getPort();
    return oss.str();
}

InetAddress TcpConnection::getLocalAddr() {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int ret = getsockname(sock_.getFd(),
                          (struct sockaddr*)&addr,
                          &len);
    if (ret == -1) {
        perror("getsockname error");
    }
    return addr;
}

InetAddress TcpConnection::getPeerAddr() {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int ret = getpeername(sock_.getFd(),
                          (struct sockaddr*)&addr,
                          &len);
    if (ret == -1) {
        perror("getpeername error");
    }
    return addr;
    
}

void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback& cb) {
    onNewConnection_ = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback& cb) {
    onClose_ = cb;
} 

void TcpConnection::setMessageCallback(const TcpConnectionCallback& cb) {
    onMessage_ = cb;
}

void TcpConnection::handleNewConnectionCallback() {
    if (onNewConnection_) {
        onNewConnection_(shared_from_this());
    } else {
        perror("onNewConnection_ == nullptr");
    }
}

void TcpConnection::handleCloseCallback() {
    if (onClose_) {
        onClose_(shared_from_this());
    } else {
        perror("onClose_ == nullptr");
    }
}

void TcpConnection::handleMessageCallback() {
    if (onMessage_) {
        onMessage_(shared_from_this());
    } else {
        perror("onMessage_ == nullptr");
    }

}

bool TcpConnection::isClosed() {
    // 看是否能读取到数据，若可以则未关闭,返回值为0，则连接已断开
    char buf[1] = {0};
    int nByte = recv(sock_.getFd(), buf, 1, MSG_PEEK);
    return nByte == 0;
}

void TcpConnection::sendInLoop(const string& msg) {
    if (loop_) {
        loop_->runInLoop(bind(&TcpConnection::send, this, msg));
    }
}
