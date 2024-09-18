#include "TcpConnection.hh"

#include <sstream>

TcpConnection::TcpConnection(int fd) 
    : sockIO_(fd),
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
        << peerAddr_.getIp() << ":" << peerAddr_.getPort()
        << "has connected\n";
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
