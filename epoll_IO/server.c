#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

/* created on ...       */
#define SERV_PORT 8888
#define EPOLL_MAX_EVENTS 1024

int main(int argc, char* argv[]) {
    // 1. 创建套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    // 1.1 设置地址可重用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. 创建套接字地址结构体
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    // 3.绑定套接字文件描述符
    int ret = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        perror("bind error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    // 4. 监听套接字
    ret = listen(listenfd, 10); 
    //第二个参数为TCP的半连接(SYN队列)和全连接(ACCEPT队列)数总和+1
    // 实际可建立的连接数为backlog+1；
    //这是一个整数类型的参数，
    //表示内核应为排队的连接请求预留的空间大小。
    //这个参数指定了在服务器拒绝接受新连接之前，
    //内核可以挂起多少个连接请求。通常，这个值应该大于等于 1
    if (ret == -1) {
        perror("listen error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }
    printf("server is listening...\n");

    // 5. 创建epoll实例 
    int epfd = epoll_create1(0);
    // 声明并定义epoll事件结构体
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    // 对listenfd进行监听
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;

    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

    struct epoll_event events_arr[EPOLL_MAX_EVENTS];// 就绪数组

    struct sockaddr_in clie_addr;//用来存储客户端的套接字地址信息
    memset(&clie_addr, 0, sizeof(clie_addr));

    char buf[BUFSIZ];// 用户态缓冲区
    int nByte;// 记录读取到的字节数
    int connfd; //已建立连接的fd

    while (1) {
        // 获取监听到的就绪事件
        int nready = epoll_wait(epfd, events_arr, EPOLL_MAX_EVENTS, -1);
        if (nready == 0) {
            perror("time out");
        } else if (nready < 0) {
            perror("epoll_wait error");
            close(listenfd);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < nready; ++i) {
            int sockfd = events_arr[i].data.fd;
            if (!(events_arr[i].events & EPOLLIN)) {// 非读事件
                continue;
            }
            if (sockfd == listenfd) {
                // 客户端有新的连接请求到来
                socklen_t len = sizeof(clie_addr);
                connfd = accept(listenfd, (struct sockaddr*)&clie_addr, &len);
                if (connfd == -1) {
                    perror("accpet error");
                    close(listenfd);
                    exit(EXIT_FAILURE);
                }
                printf("receive from %s from port %d\n",
                       inet_ntoa(clie_addr.sin_addr),
                       ntohs(clie_addr.sin_port));

                // 将新的连接添加到epoll进行监听
                ev.data.fd = connfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
            } else {
                // 处理客户端发来的数据 
                if ((nByte = read(sockfd, buf, sizeof(buf))) == 0) {
                    close(sockfd);
                    printf("client[%d] closed connection.\n", sockfd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if(ret == -1) {
                        perror("epoll_ctl error");
                    }
                } else if (nByte > 0) {
                    for (int i = 0; i < nByte; ++i) {
                        buf[i] = toupper(buf[i]); // 将小写字母变为大写
                    }
                    send(sockfd, buf, nByte, 0);
                    write(STDOUT_FILENO, buf, nByte);
                    memset(buf, 0, sizeof(buf));// 清空缓冲区
                } else { // nByte < 0
                    perror("read error");
                    close(sockfd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if(ret == -1) {
                        perror("epoll_ctl error");
                    }
                }
            }
        }
    }
    close(listenfd);
    close(epfd);

    return 0;
}

