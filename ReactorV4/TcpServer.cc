#include "TcpServer.hh"


TcpServer::TcpServer(const string& ip, unsigned short port) 
    : acceptor_(ip, port),
      loop_(acceptor_)
{

}

TcpServer::~TcpServer() {
    stop();
}

void TcpServer::start() {
    acceptor_.ready();// 服务器开启监听
    loop_.loop();// eventloop开始循环
}

void TcpServer::stop() {
    loop_.unloop();
}

void TcpServer::setAllCallback(TcpConnectionCallback&& cb1,
               TcpConnectionCallback&& cb2,
               TcpConnectionCallback&& cb3) {
    loop_.setNewConnectionCallback(std::move(cb1));// 连接建立
    loop_.setMessageCallback(std::move(cb2));// 消息到达
    loop_.setCloseCallback(std::move(cb3));// 连接断开
}
