#include <func.h>

int main(int argc, char* argv[])
{
    // ./t_fork
    printf("BEGIN\n");
    
    // idiom
    pid_t pid = fork();

    switch (pid) {
    case -1:
        error(1, errno, "fork");
    case 0:
        // 子进程
        printf("I am a baby\n");
        printf("child: pid = %d, ppid = %d\n",getpid(),getppid());
        break;
    default:
        // 父进程
        sleep(1);
        printf("who's your daddy?\n");
        printf("parent: pid = %d, childpid = %d\n", getpid(), pid);
        break;
    }
    
    printf("BYE BYE\n");
    return 0;
}

