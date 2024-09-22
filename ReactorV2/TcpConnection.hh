#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.hh"
#include "SocketIO.hh"
#include "InetAddress.hh"

#include <memory>
#include <functional>

using std::shared_ptr;
using std::function;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>;
public:
    explicit TcpConnection(int fd); 
    ~TcpConnection();

    string receive();
    void send(const string& msg);
    string toString();

    void setNewConnectionCallback(const TcpConnectionCallback& cb);
    void setCloseCallback(const TcpConnectionCallback& cb);
    void setMessageCallback(const TcpConnectionCallback& cb);
    void handleNewConnectionCallback();
    void handleCloseCallback();
    void handleMessageCallback();
    bool isClosed();
private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    SocketIO sockIO_;
    Socket sock_;
    InetAddress localAddr_;
    InetAddress peerAddr_;
    TcpConnectionCallback onNewConnection_;//连接建立
    TcpConnectionCallback onMessage_;//消息到达
    TcpConnectionCallback onClose_;// 连接断开
};

#endif

