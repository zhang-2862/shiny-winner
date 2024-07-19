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

    char buff[100] = {0};// 初始化
    

    char msg[] = "hello,server";
    ret = send(clientfd, msg, strlen(msg), 0);
    printf("send %d bytes.\n", ret);

    ret = recv(clientfd, buff, sizeof(buff), 0);
    printf("recv %d bytes.\n", ret);
    printf("recv: %s\n", buff);
    close(clientfd);

    return 0;
}

