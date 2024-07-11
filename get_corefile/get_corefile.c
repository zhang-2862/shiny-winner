#include <func.h>

int main(int argc, char* argv[])
{
    switch(fork()){
    case -1:
        error(1, errno, "fork");
    case 0:
        //子进程
        printf("child: pid = %d, ppid = %d\n",getpid(),getppid());
        printf("child: going to abort!\n");
        abort();
    default:
        //父进程
        int status;
        sleep(3);
        
        pid_t childPid = waitpid(-1,&status ,WNOHANG);
        if(childPid > 0) {
            printf("parent: %d changed state.\n", childPid);
        } else if(childPid == 0) {
            printf("parent: no child changed state.\n");
        } else {
            error(1, 0, "waitpid");
        }
        printf("parent: continue excute...\n");
        sleep(2);
        printf("parent: END.\n");
    }
    return 0;
}

