#include <func.h>
#define MAX_SIZE 128

int main(int argc, char* argv[])
{
    int fields1[2];
    if (pipe(fields1) == -1) {
        error(1, errno, "make pipe1");
    }
    int fields2[2];
    if (pipe(fields2) == -1) {
        error(1, errno, "make pipe2");
    }
    char buffer[MAX_SIZE];

    pid_t childpid = fork();
    
    switch(childpid){
    case -1:
        error(1, errno, "fork");
    case 0:
        close(fields1[0]);
        close(fields2[1]);
        write(fields1[1], "hello,father.", 13);
        read(fields2[0], buffer, MAX_SIZE);
        printf("child recived: %s\n", buffer);

        _exit(0);
    default:
        close(fields1[1]);
        close(fields2[0]);
        read(fields1[0], buffer, MAX_SIZE);
        printf("parent recived: %s\n",buffer);
        sleep(2);
        write(fields2[1], "hello,son.",10);

        exit(0);
    }
    return 0;
}

