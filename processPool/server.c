#include "processPool.h"

/* created on ...       */

int tcp_init(const char* ip, unsigned short port) {
    // 创建服务器的套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listenfd, -1, "lisenfd");

    // 设置套接字的网络地址可以重用
    int on =1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    ERROR_CHECK(ret, -1, "setsockopt");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    // 指定使用的是IPv4的地址类型 AF_INET
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);

    // 以人类可阅读的打印网络地址
    printf("%s:%d\n", inet_ntoa(serveraddr.sin_addr),
           ntohs(serveraddr.sin_port));

    // 绑定服务器的网络地址
    ret = bind(listenfd, (const struct sockaddr*)&serveraddr,
               sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "bind");

    // 监听客户端的到来
    ret = listen(listenfd, 1);
    ERROR_CHECK(ret, -1, "listen");

    return listenfd;
}

int epoll_add_rdevent(int epfd,int fd) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    return 0;
}

int epoll_del_rdevent(int epfd, int fd) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    int ret= epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    return 0;
}



