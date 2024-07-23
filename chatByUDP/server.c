#include <func.h>

/* created on      */

int main(int argc, char* argv[]) {

    // 创建UDP套接字
    int serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverfd == -1) {
        error(1, errno, "socket");
    }

    // 设置服务器地址信息
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.71.128");

    // 绑定端口
    int ret = bind(serverfd,
                   (const struct sockaddr*)&serveraddr,
                   sizeof(serveraddr));
    if (ret == -1) {
        error(1, errno, "bind");
    }

    char buff[100] = {0};

    //客户端的网络地址
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(clientaddr));
    socklen_t len = sizeof(clientaddr);

    // select
    fd_set mainfds;
    FD_ZERO(&mainfds);
    FD_SET(STDIN_FILENO, &mainfds);
    FD_SET(serverfd, &mainfds);
    
    int maxfd = serverfd + 1;

    for (;;) {
        //重置readfds
        fd_set readfds = mainfds;
        //重置clientaddr
        memset(&clientaddr, 0, sizeof(clientaddr));
        
        int events = select(maxfd, &readfds, NULL, NULL, NULL);
        switch (events) {
        case -1:
            error(1, errno, "select");
        case 0:
            printf("time out\n");
            continue;
        default:
            if (FD_ISSET(serverfd, &readfds)) {
            //接收数据
            int nbytes = recvfrom(serverfd, buff, sizeof(buff), 0,
                     (struct sockaddr*)&clientaddr, &len);
            //处理数据
            printf("recvfrom client: %s\n",buff);
            }
            if (FD_ISSET(STDIN_FILENO, &readfds)) {
            //发送数据
            read(STDIN_FILENO, buff, sizeof(buff));
            sendto(serverfd, buff, strlen(buff), 0,
                   (const struct sockaddr*)&clientaddr, len);
            }
        }
        
    }
    close(serverfd);
    return 0;
}

