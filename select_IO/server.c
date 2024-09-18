#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

#define SERV_PRORT 8888

int main(int argc, char* argv[]) {
    int listenfd, connfd, sockfd;

    struct sockaddr_in serv_addr, clie_addr;

    socklen_t clie_addr_len;

    int ret, maxfd, maxi, i, j, nready, nByte;
    
    fd_set rset, allset;

    //FD_SETSIZE定义在/usr/include/linux/posix_types.h
    //1024
    //BUFSIZ 是一个预定义的宏，通常用于表示标准 I/O 缓冲区的大小。
    //这个宏可以在 <stdio.h> 头文件中找到。在 C 语言的标准库中，
    //BUFSIZ 定义了缓冲区的默认大小，这通常是用来为文件读取和写入操作分配缓冲区的尺寸。
    //如果你正在编写代码并想要引用这个值，只需包含 <stdio.h> 头文件即可访问 BUFSIZ。
    //这个宏的具体值可能会根据不同的编译器和平台有所不同，但通常是一个相对较大的数字，
    //比如 512、1024 或者更大的数值，以确保有足够的空间来容纳一次标准的读写操作的数据量。
    //例如，在标准的 POSIX 环境下，BUFSIZ 的定义可能是 8192 字节或者更小一点。
    //然而，具体的数值应该通过查阅特定编译器的文档来确认

    int client[FD_SETSIZE];
    char buf[BUFSIZ], str[BUFSIZ];

    // 1. 创建套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket error");
        exit(1);
    }

    // 2. 地址复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // 3. 端口复用(使用了2的地址复用，端口复用可不写)
    int opt2 = 1;
    /* setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt2, sizeof(opt2)); */
    
    // 4. 绑定IP与端口号
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PRORT);

    ret = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        perror("bind error");
        close(listenfd);
        exit(1);
    }

    // 5. 服务器监听
    ret = listen(listenfd, 128);
    if (ret == -1) {
        perror("listen error");
        close(listenfd);
        exit(1);
    }
    printf("server is listening ...\n");

    // 6. select类型IO多路复用
    maxfd = listenfd; //初始化最大fd值
    
    maxi = -1; //初始化clientfd的数量
    // 待监听的存放文件描述符数组的初始化
    for (i = 0; i < FD_SETSIZE; ++i) {
        client[i] = -1;
    }
    // 清空allset
    FD_ZERO(&allset);
    //将listenfd加入监听
    FD_SET(listenfd, &allset);


    while(1) {
        rset = allset;// 重置rset
        //6.1 使用select负责监听，如果返回值大于0，表面有满足条件的连接被监听到
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0) {
            perror("select error");
            close(listenfd);
            exit(1);
        }

        // 6.2 如果有监听到的是listenfd，表示有新的请求进来
        if (FD_ISSET(listenfd, &rset)) {
            clie_addr_len = sizeof(clie_addr);
            // 7. 有新的连接，那么accpet肯定会有返回值
            connfd = accept(listenfd, (struct sockaddr*)&clie_addr, &clie_addr_len);
            if (connfd == -1) {
                perror("accept error");
                exit(1);
            }
            // 涉及到网络字节序向本机字节序的转换
            printf("receive from %s from port %d\n",
                   inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                   ntohs(clie_addr.sin_port));

            // 将新的连接添加到数组client中，该数组是为了存储建立连接的文件描述符，
            // 表面三次握手成功建立的文件描述符
            for (i = 0; i < FD_SETSIZE; ++i) {
                if (client[i] < 0) {// 找到数组中第一个未存放fd的位置，存入后跳出循环
                    client[i] = connfd;
                    break;
                }
            }

            // i超出了上限，（超过了能监听的最大文件描述符数量）
            if (i == FD_SETSIZE) {
                fputs("too many clients\n", stderr);
                exit(1);
            }

            // 将建立了三次握手的文件描述符放在allset集合中进行继续监听，
            // 如果该文件描述符后续继续刻度，表面有数据需要进行读写
            FD_SET(connfd, &allset);

            // 更新maxfd
            if (connfd > maxfd) {
                maxfd = connfd;
            }

            // 更新maxi
            if (i > maxi) {
                maxi = i;
            }

            // 如果nready为1，则直接进入下一轮while循环,
            // 因为此时必然只有一个客户端连接请求到来
            if (-- nready == 0) {
                continue;
            }
        }

        // 6.3 目的是为了遍历client数组，里面的元素如果为正，就表面该文件描述符被监听到
        // 就是老连接，可以进行数据的发送与接收
        for (i = 0; i <= maxi; ++i) {
            if ((sockfd = client[i]) < 0) {
                continue;
            }

            // 如果老的连接上有数据，表面可以进行数据传输
            if (FD_ISSET(sockfd, &rset)) {
                if ((nByte = read(sockfd, buf, sizeof(buf))) == 0) {
                    // 表面数据读完了(对应的缓冲区中没有数据了)，即连接即将断开。
                    close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else if (nByte > 0) {
                    for (j = 0; j < nByte; ++j) {
                        buf[j] = toupper(buf[j]);
                    }
                    send(sockfd, buf, nByte, 0);
                    write(STDOUT_FILENO, buf, nByte);
                    memset(buf, 0, sizeof(buf));// 清空缓冲区
                    if (--nready == 0) {
                        break;
                    }
                }
            }
        }
    }

    close(listenfd);
    close(connfd);

    return 0;
}
