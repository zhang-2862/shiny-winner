#include "Acceptor.hh"
#include "TcpConnection.hh"
#include "EventLoop.hh"
#include "ThreadPool.hh"
#include "TcpServer.hh"

#include <iostream>
#include <functional>

using std::bind;

ThreadPool* gPool = nullptr;

class Mytask {
public:
    Mytask(const string& msg, TcpConnectionPtr con)
        : msg_(msg),
          con_(con)
    {

    }

    void process() {
        // 对客户端接收的msg进行业务逻辑的处理
        // ------------------------------>
        // 将处理完后的数据发送给客户端
        con_->sendInLoop(msg_);

        //处理从客户端接收过来的msg,对msg进行业务逻辑的处理
        /* _msg; */
        //线程池在处理好业务逻辑之后，需要将数据发送给EventLoop/Reactor
        //然后由Reactor将数据发送给客户端
        //保证数据处理好之后，将数据发送给Reactor，让Reactor将数据发送给
        //客户端，而不是直接由线程池中线程发个客户端
        //
        //线程池中线程处理好业务逻辑之后，需要通知EventLoop/Reactor，这样
        //Reactor才能去接受数据，不然有可能数据从线程池发过来的时候，
        //Reactor没有接受到
        //线程池中的线程需要与Reactor的线程之间进行通信？
        //解决方案：可以使用eventfd在进程或者线程之间进行通信。
        /* _con->sendInLoop(_msg); */ //---------------------------------
        //线程池中的线程处理好业务逻辑之后，需要将数据发给Reactor，但是
        //其实使用的是TcpConnection的对象进行发送的，那么处理好之后的数据
        //_msg其实还只在TcpConnection中，要想将数据发给Reactor，必须要
        //让TcpConnection知道EVentLoop存在，所以在TcpConnection中增加了
        //EVentLoop的指针，这样就可以让TcpConnection知道EventLoop的存在
    }

private:
    string msg_;
    TcpConnectionPtr con_;
};

void onNewConnection(const TcpConnectionPtr& con) {
    std::cout << con->toString() << " has connected." << std::endl;
}

void onClose(const TcpConnectionPtr& con) {
    std::cout << con->toString() << " has closed." << std::endl;
}

void onMessage(const TcpConnectionPtr& con) {
    /* string msg = con->receive(); */
    /* std::cout << "recv msg from client: " << msg << std::endl; */ 
    /* con->send(msg); */
    // 以上为ReactorV2版本
    
    // 接收客户端数据
    string msg = con->receive();
    std::cout << ">>>recv msg from client: " << msg << std::endl;
    // 让线程池处理业务逻辑
    Mytask task(msg, con);
    gPool->addTask(bind(&Mytask::process, task));
}

void test() {
    /* Acceptor acceptor("127.0.0.1", 8080); */
    /* acceptor.ready(); */

    /* EventLoop loop(acceptor); */
    /* // 注册相应处理函数 */
    /* loop.setNewConnectionCallback(onNewConnection); */
    /* loop.setCloseCallback(onClose); */
    /* loop.setMessageCallback(onMessage); */

    /* loop.loop(); */

    // 上面为之前v2 版本

    TcpServer server("127.0.0.1", 8080);

    ThreadPool pool(4, 10);
    pool.start();
    gPool = &pool;
    server.setAllCallback(std::move(onNewConnection),
                          std::move(onMessage),
                          std::move(onClose));
    server.start();

}

int main(int argc, char* argv[]) {
    test();
    return 0;
}

