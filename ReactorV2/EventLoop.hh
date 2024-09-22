#ifndef __EventLoop_H__
#define __EventLoop_H__

#include <vector>
#include <memory>
#include <map>
#include <functional>

using std::vector;
using std::shared_ptr;
using std::map;
using std::function;

class Acceptor;
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>;

class EventLoop {
public:
    EventLoop(Acceptor& acceptor);
    ~EventLoop();
    void loop();
    void unloop();
private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int fd);
    int createEpollFd();
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);
public:
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setMessageCallback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);

private:
    int epfd_;
    vector<struct epoll_event> evtList_;
    bool isLooping_;
    Acceptor& acceptor_;
    map<int, TcpConnectionPtr> conns_; 
    // 回调函数
    TcpConnectionCallback onNewConnection_;//连接建立
    TcpConnectionCallback onMessage_;//消息到达
    TcpConnectionCallback onClose_;// 连接断开
};

#endif

