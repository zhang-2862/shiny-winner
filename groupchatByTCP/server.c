#include "func.h"

int main(int argc, char* argv[]) {

    // 创建服务器的监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        error(1, errno, "socket");
    }

    // 设置套接字的网络地址可以重用
    int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (ret == -1) {
        error(1, errno, "setsockopt");
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.142.129");

    // 以人类可阅读的方式打印网络地址
    printf("%s: %d\n",
           inet_ntoa(serveraddr.sin_addr),
           ntohs(serveraddr.sin_port));

    // 绑定服务器的网络地址
    ret = bind(listenfd, (const struct sockaddr*)&serveraddr,
               sizeof(serveraddr));
    if (ret == -1) {
        error(1, errno, "bind");
    }

    // 监听客户端的到来
    ret = listen(listenfd, 1);
    if (ret == -1) {
        error(1, errno, "listen");
    }
    printf("server is listening...\n");


    char buffer[1000] = {0};// 初始化
    char conns[1000] = {0};// 初始化

    // 创建监听集合,并进行初始化
    fd_set mainfds;
    FD_ZERO(&mainfds);

    // 进入聊天
    for (;;) {
        FD_SET(listenfd, &mainfds);

        for (int i = 0; i < 1000; ++i) {
            if (conns[i] != 0) {
                FD_SET(conns[i], &mainfds);
            }
        }

        int events = select(1000, &mainfds, NULL, NULL, NULL);

        switch (events) {
        case -1:
            error(1, errno, "select");
        case 0:
            printf("time out");
            continue;
        default:
            // 对于新连接
            if (FD_ISSET(listenfd, &mainfds)) {
                struct sockaddr_in clientaddr;
                memset(&clientaddr, 0, sizeof(clientaddr));
                socklen_t len = sizeof(clientaddr);
                printf("len: %d\n", len);

                //通过accept的第二个参数可以获取到客户端的网络地址
                int peerfd = accept(listenfd,
                                    (struct sockaddr*)&clientaddr, &len);

                printf("peerfd: %d\n", peerfd);
                printf("client addr: %s:%d has connected.\n",
                       inet_ntoa(clientaddr.sin_addr),
                       ntohs(clientaddr.sin_port));

            }
        }
    }
end:
    close(peerfd);
    close(listenfd);

    return 0;
}

