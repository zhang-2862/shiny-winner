#include <func.h>
#define MAX_BUFF_SIZE 1024
#define MAX_SIZE 4096

/* created on      */

int main(int argc, char* argv[]) {
    if (argc < 2){
        error(1, 0, "argc < 2");
    }
    // 创建服务器监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        error(1, errno, "socket");
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.71.128");

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
    printf("server is listenning...\n");

    // 创建客户端的地址信息结构体
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(clientaddr));
    socklen_t len = sizeof(clientaddr);
    printf("len: %d\n", len);

    while (1) {
        // 获取与对端进行交互的文件描述符
        int peerfd = accept(listenfd, NULL, NULL);
        char buff[MAX_BUFF_SIZE] = {0};
        
        //接受请求数据
        int ret = recv(peerfd, buff, sizeof(buff), 0);
        printf("\nrecv %d bytes.\n", ret);
        printf("%s\n", buff);

        // 打开图片文件
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            error(1, errno, "open %s",argv[1]);
        }
        // 计算实际的文件大小
        lseek(fd, 0, SEEK_END);
        off_t file_size = lseek(fd, 0, SEEK_CUR);
        lseek(fd, 0, SEEK_SET);
        
        //发送响应数据
        char response[MAX_SIZE] = {0};
        // 拼接数据
        const char* startline = "HTTP/1.1 200 OK\r\n";
        const char* headers = "Server: MyHttpServer1.0\r\n"
            "Connection: close\r\n"
            "Content-Type: image/jpeg\r\n"
            "Content-Lenth: "; 
        const char* emptyLine = "\r\n";
        sprintf(response,"%s%s%ld\r\n%s",
                startline,
                headers,
                (long)file_size, //文件大小
                emptyLine);
        send(peerfd, response, strlen(response), 0);

        // 发送图片
        size_t nbytes;
        while ((nbytes = read(fd, buff, sizeof(buff))) > 0) {
            send(peerfd, buff, nbytes, 0);
        }
        close(peerfd);
    }

    close(listenfd);
    return 0;
}

