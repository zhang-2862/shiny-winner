#include "Acceptor.hh"
#include "TcpConnection.hh"
#include "EventLoop.hh"

#include <iostream>

void onNewConnection(const TcpConnectionPtr& con) {
    std::cout << con->toString() << " has connected." << std::endl;
}

void onClose(const TcpConnectionPtr& con) {
    std::cout << con->toString() << " has closed." << std::endl;
}

void onMessage(const TcpConnectionPtr& con) {
    string msg = con->receive();
    std::cout << "recv msg from client: " << msg << std::endl; 
    con->send(msg);
}

void test() {
    Acceptor acceptor("127.0.0.1", 8080);
    acceptor.ready();

    EventLoop loop(acceptor);
    // 注册相应处理函数
    loop.setNewConnectionCallback(onNewConnection);
    loop.setCloseCallback(onClose);
    loop.setMessageCallback(onMessage);

    loop.loop();
}

int main(int argc, char* argv[]) {
    test();
    return 0;
}

