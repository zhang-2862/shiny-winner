#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* created on ...       */
#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888

int main(int argc, char* argv[]) {
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    // 创建套接字地址结构体
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);

    // 连接服务器
    int ret = connect(cfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        perror("connect error");
        close(cfd);
        exit(EXIT_FAILURE);
    }

    printf("connect success.\n");

    char buf[BUFSIZ];

    while (1) {
        fgets(buf, sizeof(buf), stdin);

        send(cfd, buf, strlen(buf), 0);

        memset(buf, 0, sizeof(buf));
        int nByte = recv(cfd, buf, sizeof(buf), 0);
        write(STDIN_FILENO, buf,nByte);
    }


    return 0;
}

