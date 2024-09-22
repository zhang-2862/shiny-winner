#include "Acceptor.hh"
#include "TcpConnection.hh"
#include "InetAddress.hh"

#include <iostream>

void test() {
    Acceptor acceptor("127.0.0.1", 8080);
    acceptor.ready();

    int fd = acceptor.accept();
    TcpConnection con(fd);
    std::cout << con.toString() << " has connected." << std::endl;
    while (1) {
        string msg = con.receive();
        std::cout << "recv msg from client: " << msg << std::endl; 
        con.send(msg);
    }
}

int main(int argc, char* argv[]) {
    test();
    return 0;
}

