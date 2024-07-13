#include <func.h>

/* created on  24/7/13    */

void handler(int signo) {
    switch (signo) {
    case SIGINT:
        printf("Caught SIGINT\n");
        break;
    case SIGQUIT:
        printf("Caught SIGQUIT\n");
        break;
    case SIGTSTP:
        printf("Caught SIGTSTP\n");
        break;
    default:
        printf("Unkown %d\n", signo);
    }
}

int main(int argc, char* argv[]) {
    pid_t pid = getpid();
    printf("pid: %d\n",pid);

    sighandler_t oldhandler = signal(SIGINT, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal %d", SIGINT);
    }
    oldhandler = signal(SIGTSTP, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal %d", SIGTSTP);
    }
    oldhandler = signal(SIGQUIT, handler);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal %d", SIGQUIT);
    }
    for(;;){
        sleep(5);
    }
    return 0;
}
