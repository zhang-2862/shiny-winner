#include <func.h>

int simple_system(const char* command) {
    pid_t childPid = fork();
    int status;

    switch (childPid) {
    case -1:
        return -1;
    case 0:
        execl("/bin/sh", "sh", "-c", command, NULL);
        _exit(127);
    default:
        if (waitpid(childPid, &status, 0) == -1){
            return -1;
        } else {
            return status;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2){
        error(1, errno, "Usage: command");
    }
    int ret = simple_system(argv[1]);
    if(ret == -1) {
        printf("error.\n");
    } else {
        printf("status: %d\n",ret);
    }
    return 0;
}

