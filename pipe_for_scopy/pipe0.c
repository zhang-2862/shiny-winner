#include <func.h>
#define MAXSIZE 4096

int main(int argc, char* argv[])
{
    if(argc != 2){
        error(1,0,"Usage: file name.");
    }
    int fd_r = open(argv[1], O_RDONLY);
    if (fd_r == -1) {
        error(1, errno, "open file");
    }
    if(mkfifo("pipe",0660) == -1){
        error(1, errno,"make pipe ");
    }
    int fd0 = open("pipe", O_WRONLY);
    if (fd0 == -1) {
        error(1, errno, "open pipe");
    }
    printf("Established\n");
    char recvbuffer[MAXSIZE];
    int bytes;
    while ((bytes = read(fd_r,recvbuffer,MAXSIZE)) > 0) {
        write(fd0,recvbuffer, bytes);    
    }
    close(fd_r);
    close(fd0);
    return 0;
}

