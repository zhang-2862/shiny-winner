#include "EventLoop.hh"
#include "Acceptor.hh"
#include "TcpConnection.hh"

#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>


EventLoop::EventLoop(Acceptor& acceptor) 
    : epfd_(createEpollFd()),
      evtList_(1024),
      isLooping_(false),
      acceptor_(acceptor),
      conns_()
{
    // 监听listenfd
    addEpollReadFd(acceptor_.fd());
}

EventLoop::~EventLoop() {
    close(epfd_);
}

void EventLoop::loop() {
    isLooping_ = true;
    while (isLooping_) {
        waitEpollFd();
    }
}

void EventLoop::unloop() {
    isLooping_ = false;
}

void EventLoop::waitEpollFd() {
    int nready = 0;
    do {
        nready = epoll_wait(epfd_, evtList_.data(), evtList_.size(), 3000);
    } while (nready == -1 && errno == EINTR);
    if (nready == -1) {
        printf("nready == -1");
        return;
    } else if (nready == 0) {
        printf("epoll_wait time out.\n");
    } else {
        // 处理新连接、老连接
        for (int i = 0; i < nready; ++i) {
            int sockfd = evtList_[i].data.fd;
            if (sockfd == acceptor_.fd()) {
                handleNewConnection();
            } else {
                handleMessage(sockfd);
            }
        }
    }
}

void EventLoop::handleNewConnection() {
    int connfd = acceptor_.accept();
    if (connfd == -1) {
        perror("handleNewConnection accpet() error");
        return;
    } else {
        // 监听新连接
        addEpollReadFd(connfd);
        // 创建新的TcpConnection对象
        TcpConnectionPtr conPtr(new TcpConnection(connfd));
        // 将对象放入map
        conns_[connfd] = conPtr;
        // 将三个回调函数传入新的TcpConnection对象
        conPtr->setNewConnectionCallback(onNewConnection_);
        conPtr->setCloseCallback(onClose_);
        conPtr->setMessageCallback(onMessage_);

        // accpet成功调用，说明连接已建立，此时执行相应回调函数
        conPtr->handleNewConnectionCallback();
    }
}

void EventLoop::handleMessage(int fd) {
    auto it = conns_.find(fd);
    if (it != conns_.end()) {
        // 说明连接存在
        // 检查连接是否断开
        bool flag = it->second->isClosed();
        if (flag) {
            // 连接断开，进行相应处理
            it->second->handleCloseCallback();
            delEpollReadFd(fd);//删除监听
            conns_.erase(it);// 并从map中删除
            
        } else {
            it->second->handleMessageCallback();
        }
    } else {
        printf("连接不存在！\n");
    }
}

int EventLoop::createEpollFd() {
    int ret = epoll_create1(0);
    if (ret == -1) {
        perror("createEpollFd error");
        return -1;
    }
    return ret;
}

void EventLoop::addEpollReadFd(int fd) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;

    int ret = epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev);
    if (ret == -1) {
        perror("addEpollReadFd");
    }
    
}

void EventLoop::delEpollReadFd(int fd) {
    int ret = epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, NULL);
    if (ret == -1) {
        perror("delEpollReadFd error");
    }
}

void EventLoop::setNewConnectionCallback(TcpConnectionCallback&& cb) {
    onNewConnection_ = std::move(cb);
}

void EventLoop::setMessageCallback(TcpConnectionCallback&& cb) {
    onMessage_ = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback&& cb) {
    onClose_ = std::move(cb);
}
