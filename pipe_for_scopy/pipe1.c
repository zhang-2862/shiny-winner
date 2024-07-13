#include <func.h>
#define MAXSIZE 4096

int main(int argc, char* argv[])
{
    if(argc != 2){
        error(1,0,"Usage: file name.");
    }
    int fd_w = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_w == -1) {
        error(1, errno, "open file");
    }
    int fd1 = open("pipe", O_RDONLY);
    if (fd1 == -1) {
        error(1, errno, "open pipe");
    }

    printf("Established\n");
    char recvbuffer[MAXSIZE];
    int bytes;
    while ((bytes = read(fd1,recvbuffer,MAXSIZE)) > 0) {
        write(fd_w,recvbuffer, bytes);    
    }
    close(fd_w);
    close(fd1);
    return 0;
}

