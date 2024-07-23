#include <func.h>

/* created on      */

int main(int argc, char* argv[]) {

    // 创建UDP套接字
    int clientfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientfd == -1) {
        error(1, errno, "clientfd");
    }

    // 设置服务器地址信息
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.71.128");
    socklen_t len = sizeof(serveraddr);

    fd_set mainfds;
    FD_ZERO(&mainfds);
    FD_SET(STDIN_FILENO, &mainfds);
    FD_SET(clientfd, &mainfds);

    int maxfd = clientfd;
    char buff[100];
    
    // 循环读写
    for (;;) {
        // 重置缓冲区以及监听集合
        memset(buff, 0, sizeof(buff));
        fd_set readfds = mainfds;

        //select
        int events = select(maxfd, &readfds, NULL, NULL, NULL);
        switch (events) {
        case -1:
            error(1, errno, "select");
        case 0:
            printf("time out\n");
            continue;
        default:
            if (FD_ISSET(clientfd, &readfds)) {
                // 发生读事件，读取信息
                int ret = recvfrom(clientfd, buff, sizeof(buff), 0,
                         (struct sockaddr*)&serveraddr, &len);
                printf("recvfrom server: %s\n", buff);
            }
            if (FD_ISSET(STDIN_FILENO, &readfds)) {
                // 键盘缓冲区有数据
                read(STDIN_FILENO, buff, sizeof(buff));
                // 发送数据
                sendto(clientfd, buff, strlen(buff), 0,
                       (const struct sockaddr*)&serveraddr, len);
            }
        }
    }

    close(clientfd);
    return 0;
}

