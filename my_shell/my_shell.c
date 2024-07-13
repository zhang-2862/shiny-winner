#include <func.h>
#define MAX_SIZE 128

/* created on  24/7/13    */

void print_wstatus(int status) {
    if (WIFEXITED(status)) { 
        int exit_code = WEXITSTATUS(status);
        printf("exit_code = %d", exit_code);
    } else if (WIFSIGNALED(status)) {
        int signo = WTERMSIG(status); 
        printf("term_sig= %d", signo);
    }
#ifdef WCOREDUMP
        if (WCOREDUMP(status)) {
            printf(" (core dump)");
        }
#endif
    printf("\n");
}

int main(int argc, char* argv[]) {
    char buffer[MAX_SIZE];
    for(;;) {
        printf(">");
        fgets(buffer, MAX_SIZE, stdin);
        buffer[strcspn(buffer,"\n")]='\0';//将换行符替换为'\0'
        if (strcmp(buffer,"exit") == 0) {
            break;
        }
        pid_t childPid = fork();
        switch(childPid) {
        case -1:
            error(1, errno, "fork");
        case 0:
            execlp("sh","sh","-c",buffer,NULL);
            _exit(127);
        default:
            int status;
            if (waitpid(childPid, &status, 0) == -1) {
                return -1;
            } else {
                print_wstatus(status);
            }
        }
    }
    return 0;
}

