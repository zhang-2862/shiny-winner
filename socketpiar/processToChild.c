#include <func.h>

/* created on      */

int sendFd(int pipefd, int fd);
int recvFd(int pipefd, int* pfd);

int main(int argc, char* argv[]) {
    int fds[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
    pid_t pid = fork();
    if (pid < 0) {
        close(fds[0]); //关闭读端
        // 打开一个文件，模拟传递的文件描述符
        int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 664);
        printf("parent fd: %d\n", fd);
        sendFd(fds[1], fd);
        wait(NULL);
        close(fd);
    } else {
        // 父进程
        close(fds[1]); //关闭写端

        int childfd = -1;
        // 通过管道读取夫进程传递过来的fd
        recvFd(fds[0], &childfd);
        printf("childfd %d, fds[0]: %d.\n", childfd, fds[0]);

        // 通过childfd来写文件
        int nbytes = write(childfd, "hello child.", 12);
        printf("write nbytes: %d\n", nbytes);
    }
    return 0;
}

