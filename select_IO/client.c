#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888

int main(int argc, char* argv[]) {
    int cfd;
    struct sockaddr_in serv_addr;
    char buf[BUFSIZ];
    int nByte;

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1) {
        perror("socket error");
        exit(1);
    }

    memset(&serv_addr, 0 , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);

    int ret = connect(cfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        perror("connect error");
        close(cfd);
        exit(1);
    }
    printf("connect seccuss.\n");

    while (1) {
        fgets(buf, sizeof(buf), stdin); // hello world ---> hello world\n\0
        send(cfd, buf, strlen(buf), 0);

        memset(buf, 0, sizeof(buf));
        nByte = recv(cfd, buf, sizeof(buf), 0);

        write(STDIN_FILENO, buf, nByte); 
    }


    close(cfd);
    return 0;
}

