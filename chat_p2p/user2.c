#include <func.h>
#define MAX_LINE 512

int main(int argc, char* argv[]) {
    
    int fd1 = open("pipe1", O_WRONLY);
    if (fd1 == -1) {
        error(1, errno, "oepn pipe1");
    }
    int fd2 = open("pipe2", O_RDONLY);
    if (fd1 == -1) {
        error(1, errno, "oepn pipe2");
    }
    
    printf("Established.\n");
    char recvline[MAX_LINE];
    char sendline[MAX_LINE];

    fd_set main_fdset;
    //初始化
    FD_ZERO(&main_fdset);

    FD_SET(STDIN_FILENO, &main_fdset);
    int max_fd=STDIN_FILENO; 

    FD_SET(fd2,&main_fdset);
    if (fd2 > max_fd) {
        max_fd = fd2;
    }

    for(;;) {
        fd_set readset = main_fdset; 

        //struct timeval timeout = {5,0};
        int events = select(max_fd+1, &readset, NULL, NULL, NULL);

        switch(events){
        case -1:
            error(1, errno, "select");
        case 0:
            error(1,0,"timeout");
            continue;
        default:
            //printf("timeout: tv_sec = %ld, tv_usec= %ld\n",timeout.tv_sec,timeout.tv_usec); 
            if (FD_ISSET(STDIN_FILENO, &readset)) {
                fgets(sendline, MAX_LINE, stdin);
                write(fd1, sendline, strlen(sendline)+1);
            }
            if (FD_ISSET(fd2, &readset)) {
                int bytes = read(fd2, recvline, MAX_LINE);
                if (bytes == 0) {
                    //说明写端已经关闭
                    goto end;
                } else if (bytes == -1) {
                    error(1, errno, "read pipe");
                }
                printf("frome user1: %s",recvline);
            }
        }
    }
end:
        close(fd1);
        close(fd2);
        printf("disconnection.\n");
        return 0;
}
