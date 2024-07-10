#include <func.h>

int main(int argc, char* argv[])
{
    printf("BEGIN\n");
    pid_t pid = fork();
    switch (pid) {
    case -1:
        error(1, errno, "fork");
    case 0: 
        // 子进程
        printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
        printf("child: cwd is %s\n",getcwd(NULL, 0));
        if(chdir("/home/zg/learn-linux/") == -1){
            error(1, errno, "chdir");
        }
        printf("child: after change dir, cwd is %s\n",getcwd(NULL, 0));
        break;
    default:
        //父进程
        printf("parent: pid = %d, childpid = %d\n", getpid(), pid);
        printf("parent: cwd is %s\n",getcwd(NULL, 0));
        sleep(5);
        printf("parent: after 5 seconds, cwd is %s\n",getcwd(NULL, 0));
    }
    return 0;
}

