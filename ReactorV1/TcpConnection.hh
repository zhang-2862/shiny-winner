#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.hh"
#include "SocketIO.hh"
#include "InetAddress.hh"

class TcpConnection {
public:
    explicit TcpConnection(int fd); 
    ~TcpConnection();

    string receive();
    void send(const string& msg);
    string toString();
private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    SocketIO sockIO_;
    Socket sock_;
    InetAddress localAddr_;
    InetAddress peerAddr_;
};

#endif

