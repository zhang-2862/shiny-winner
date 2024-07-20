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
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.142.129");
    
    // 连接服务器

    int ret = connect(clientfd, (struct sockaddr*)&serveraddr,
                      sizeof(serveraddr));
    if (ret == -1) {
        error(1, errno, "connect");
    }
    printf("connect success.\n");

    char send_buf[1000] = {0};// 初始化
    char recv_buf[1000] = {0};
    
    for (;;) {
        // 从键盘读取消息
        ret = read(STDIN_FILENO, send_buf, sizeof(send_buf));
        if (ret == -1) {
            error(1, errno, "read message");
        }

        // 将结尾的换行符去除
        ret = send(clientfd, send_buf, strlen(send_buf) - 1, 0);
        if (ret) {
            error(1, errno, "send message");
        }
        printf("send %d bytes.\n", ret);

        ret = recv(clientfd, recv_buf, sizeof(recv_buf), 0);
        if (ret) {
            error(1, errno, "recv message");
        }
        printf("recv: %s\n", recv_buf);
        printf("recv %d bytes.\n", ret);

        close(clientfd);
    }

    return 0;
}

