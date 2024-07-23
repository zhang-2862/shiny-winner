#include <func.h>

/* created on      */

int main(int argc, char* argv[]) {

    // 创建服务器的监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        error(1, errno, "socket");
    }

    // 设置套接字的网络地址可以重用
    int on =1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (ret == -1) {
        error(1, errno, "setsockopt");
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    // 指定使用的是IPv4的地址类型 AF_INET
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.71.128");

    // 以人类可阅读的方式打印网络地址
    printf("%s:%d\n,",
           inet_ntoa(serveraddr.sin_addr),
           ntohs(serveraddr.sin_port));
    
    // 绑定服务器的网络地址
    ret = bind(listenfd, (const struct sockaddr*)&serveraddr,
               sizeof(serveraddr));
    if (ret == -1) {
        error(1, errno, "bind");
    }

    // 监听客户端的到来
    ret = listen(listenfd, 10);

    //创建epoll的实例
    int epfd = epoll_create1(0);
    if (epfd == -1) {
        error(epfd, errno, "epoll_create1");
    }
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    if (ret == -1) {
        error(1, errno, "epoll_ctl");
    }

    // 存储消息
    char buff[100] = {0};

    //用户态用来存储就绪的文件描述符
    struct epoll_event eventsArr[100] = {0};

    int nready = 0;

    // 事件循环
    while (1) {
        nready = epoll_wait(epfd, eventsArr, 100, -1);
        printf("nready: %d\n", nready);

        // 当nready的值大于0时，就已经拿到了发生了就绪事件的fd
        for (int i = 0; i < nready; ++i) {
            int fd = eventsArr[i].data.fd;
            // 对于新连接的处理
            if (fd == listenfd) {
                // 当fd与listenfd相等时，表示listenfd已就绪(即有客户端请求连接)
                //处理一个客户端的请求

                struct sockaddr_in clientaddr;
                socklen_t len = sizeof(clientaddr);
                int peerfd = accept(listenfd, (struct sockaddr*)&clientaddr, &len);
                printf("client %s:%d has connected.\n",
                       inet_ntoa(clientaddr.sin_addr),
                       ntohs(clientaddr.sin_port));

                // epoll对peerfd进行监听，添加到红黑树上，只需要进行一次监听即可
                ev.events = EPOLLIN | EPOLLOUT;
                ev.data.fd = peerfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, peerfd, &ev);
                if (ret == -1) {
                    error(1, errno, "epoll_ctl");
                }
            } else {
                printf("......\n");
                //if (eventsArr[i].events & EPOLLIN) {
                    // 已经建立好的连接发送数据后
                    memset(buff, 0, sizeof(buff));
                    ret = recv(fd, buff, sizeof(buff), 0);
                    if (ret == -1) {
                        error(1, errno, "recv");
                    }
                    if (ret == 0) {
                        // recv的返回值为0，说明连接已经断开了
                        //故不需要再对fd进行监听， 从epfd对应的红黑树上删除掉
                        ev.events = EPOLLIN;
                        ev.data.fd = fd;
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
                        if (ret == -1) {
                            error(1, errno, "epoll_ctl");
                        }
                        printf("bye\n");
                        close(fd);//关闭套接字
                        continue;
                    }
                    // 回显操作
                    printf("ret: %d, recv: %s\n", ret, buff);
                    if (send(fd, buff, ret, 0) == -1) {
                        error(1, errno, "send");
                    }
               // }
            }
#if 0
            if (eventsArr[i].events & EPOLLOUT) {
                // 写事件会一直被触发，因为内核发送缓冲区有空间
                printf("handle Write events.\n");
                // 如果不需要再出发写事件，那就需要暂时删掉写事件的触发
                ev.events = EPOLLOUT;
                ev.data.fd = fd;
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
            }
#endif

        }
    }

    close(listenfd);
    close(epfd);
    
    return 0;
}

