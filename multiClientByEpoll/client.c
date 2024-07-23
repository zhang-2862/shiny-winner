#include "func.h"

int main(int argc, char* argv[]) {

    // 创建客户端的套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0) {
        error(1, errno, "socket");
    }
    printf("clientfd: %d\n", clientfd);

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.71.128");

    // 连接服务器

    int ret = connect(clientfd, (struct sockaddr*)&serveraddr,
                      sizeof(serveraddr));
    if (ret == -1) {
        error(1, errno, "connect");
    }
    printf("connect success.\n");

    char send_buf[1000] = {0};// 初始化
    char recv_buf[1000] = {0};

    // 创建监听集合,并进行初始化
    fd_set mainfds;
    FD_ZERO(&mainfds);
    FD_SET(STDIN_FILENO, &mainfds);
    FD_SET(clientfd, &mainfds);
    int maxfd = clientfd+1;

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
            if (FD_ISSET(clientfd, &readfds)) {
                ret = recv(clientfd, recv_buf, sizeof(recv_buf), 0);
                if (ret == -1) {
                    error(1, errno, "recv message");
                }
                // 如果接受到的字符为0，则说明服务端已经关闭连接
                if (ret == 0) {
                    printf("the server is disconnected.\n");
                    break;
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
                ret = send(clientfd, send_buf, strlen(send_buf) - 1, 0);
                if (ret == -1) {
                    error(1, errno, "send message");
                }
                // 每发送一条消息后换行
                printf("\n");
                memset(send_buf, 0, sizeof(send_buf));
            }
        }
    }
    close(clientfd);

    return 0;
}

