#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SERV_PORT 8080
#define OPEN_MAX 8192 //客户端最多连接数
/* created on ...       */

int main(int argc, char* argv[]) {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    int ret = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        perror("bind error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    ret = listen(listenfd, 128);
    if (ret == -1) {
        perror("listenfd error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }
    printf("server is listening...\n");

    struct pollfd client[OPEN_MAX];

    client[0].fd = listenfd;// 将listenfd放入监听数组中
    client[0].events = POLLIN; // 监听读事件
                               
    //待监听的存放文件描述符数组的初始化,注意这里从1开始
    for (int i = 1; i < OPEN_MAX; ++i) {
        client[i].fd = -1;
    }

    int maxi = 0; //监听fd数组的最大索引值

    char buf[BUFSIZ];//用户态缓存
    int nByte = 0; // 接收到的字节数

    while (1) {
        int nready = poll(client, maxi + 1, -1);// 索引值从0开始，数量为最大索引加1
        if (nready < 0) {
            perror("poll error");
            close(listenfd);
            exit(EXIT_FAILURE);
        } else if (nready == 0) {
            continue;
        } 

        if (client[0].revents & POLLIN) {
           // 有新的请求到来
           socklen_t len = sizeof(serv_addr);
           int connfd = accept(listenfd, (struct sockaddr*)&serv_addr, &len);
           if (connfd == -1) {
               perror("poll error");
               close(listenfd);
               exit(EXIT_FAILURE);
           }
           // 打印新连接的IP与端口号
           printf("receive from %s from port %d\n",
                  inet_ntoa(serv_addr.sin_addr),
                  ntohs(serv_addr.sin_port));
           // 加入监听数组
           int i = 1;
           for (; i < OPEN_MAX; ++i) {
               // 遍历数组，找到一个未存放连接的位置
               if (client[i].fd == -1) {
                   client[i].fd = connfd;
                   client[i].events = POLLIN;
                   break;
               }
           }
           //i超过了上线，超过能监听的最大文件描述符数
            if(i == OPEN_MAX)//select监听的文件描述符有上限，最大只能监听1024个
            {
                fputs("too many clients\n", stderr);
                exit(1);
            }
            if(i > maxi)
            {
                maxi = i;//因为文件描述符有新增，导致自定义数组有变化，所以需要重新修改maxi的值
            }

            //如果nready为1,那就继续进行while循环，而不用
            //走6.3出的for循环，提升效率
            if(--nready == 0)
            {
                continue;
            }
        }
            // 处理客户端连接发送的数据
            for (int i = 1; i <= maxi; ++i) {
                if (client[i].fd < 0) {
                    continue;
                }
                if (!(client[i].revents & POLLIN)) {
                    // 非读事件
                    continue;
                } else {
                    // 接收并处理数据
                    if ((nByte = recv(client[i].fd, buf, sizeof(buf), 0)) == 0) {
                        // 说明客户端已经断开连接
                        printf("client[%d] close connection.\n", client[i].fd);
                    } else if (nByte > 0) {
                        // 将数据由小写转为大写
                        for (int i = 0; i < nByte; ++i) {
                            buf[i] = toupper(buf[i]);
                        }
                        //发送给客户端
                        send(client[i].fd, buf, nByte, 0);
                        //之后将处理后的数据输出到屏幕
                        write(STDIN_FILENO, buf, nByte); 
                    } else {
                        perror("recv error");
                        close(client[i].fd);
                        client[i].fd = -1;//重新置为-1
                    }
                }
                if(--nready == 0)
                {
                    continue;
                }
            }
    }
    close(listenfd);

    return 0;
}

