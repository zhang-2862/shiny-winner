#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "Acceptor.hh"
#include "EventLoop.hh"

class TcpServer {
public:
    TcpServer(const string& ip, unsigned short port);
    ~TcpServer();
    void start();
    void stop();
    void setAllCallback(TcpConnectionCallback&& cb1,
                   TcpConnectionCallback&& cb2,
                   TcpConnectionCallback&& cb3);

private:
    Acceptor acceptor_;
    EventLoop loop_;
};

#endif

