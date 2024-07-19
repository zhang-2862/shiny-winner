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
    
    while (1) {
        // 监听客户端的到来
        ret = listen(listenfd, 1);
        if (ret == -1) {
            error(1, errno, "listen");
        }
        printf("server is listening.\n");
        
        struct sockaddr_in clientaddr;
        memset(&clientaddr, 0, sizeof(clientaddr));
        socklen_t len = sizeof(clientaddr);
        printf("len: %d\n", len);

        //通过accept的第二个参数可以获取到客户端的网络地址
        int peerfd = accept(listenfd,
                            (struct sockaddr*)&clientaddr, &len);
        
        printf("peerfd: %d\n", peerfd);
        printf("client addr: %s:%d\n",
               inet_ntoa(clientaddr.sin_addr),
               ntohs(clientaddr.sin_port));

        char send_buf[1000] = "hello,client";
        char recv_buf[1000]={0};

        ret = recv(peerfd, recv_buf, sizeof(recv_buf), 0);
        printf("recv %d bytes.\n", ret);
        printf("recg: %s\n", recv_buf);
        
        ret = send(peerfd, send_buf, strlen(send_buf), 0);
        printf("send %d bytes.\n", ret);

        close(peerfd);
    }

    close(listenfd);

    return 0;
}

