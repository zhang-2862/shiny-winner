#include "func.h"

int main(int argc, char* argv[]) {

    // 创建服务器的监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        error(1, errno, "socket");
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
    int ret = bind(listenfd, (const struct sockaddr*)&serveraddr,
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

    char send_buf[1000] = {0};// 初始化
    char recv_buf[1000] = {0};

    // 创建监听集合,并进行初始化
    fd_set mainfds;
    FD_ZERO(&mainfds);
    FD_SET(STDIN_FILENO, &mainfds);
    FD_SET(peerfd, &mainfds);
    int maxfd = peerfd+1;

    // 进入聊天
    for (;;) {
        fd_set readfds = mainfds;
        int events = select(maxfd, &readfds, NULL, NULL, NULL);

        switch (events) {
        case -1:
            error(1, errno, "select");
        case 0:
            printf("time out");
            continue;
        default:
            if (FD_ISSET(peerfd, &readfds)) {
                ret = recv(peerfd, recv_buf, sizeof(recv_buf), 0);
                if (ret == -1) {
                    error(1, errno, "recv message");
                }
                // 如果接受到的字符为0，则说明客户端已关闭连接
                if (ret == 0) {
                    printf("the client is disconnected.\n");
                    goto end;
                }
                printf("recv: %s (recv %d bytes.)\n\n", recv_buf, ret);
                memset(recv_buf, 0, sizeof(recv_buf));
            }
            
            if (FD_ISSET(STDIN_FILENO, &readfds)) {
                // 从键盘读取消息
                ret = read(STDIN_FILENO, send_buf, sizeof(send_buf));
                if (ret == -1) {
                    error(1, errno, "read message");
                }
                // 将结尾的换行符去除
                ret = send(peerfd, send_buf, strlen(send_buf) - 1, 0);
                if (ret == -1) {
                    error(1, errno, "send message");
                }
                printf("\n");
                memset(send_buf, 0, sizeof(send_buf));
            }
        }
    }
end:
    close(peerfd);
    close(listenfd);

    return 0;
}

