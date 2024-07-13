#include <func.h>

/* created on 24/7/13     */

int main(int argc, char* argv[]) {
    if (argc < 3) {
        error(1, 0, "Usage: %s signo pid ...", argv[0]);
    }
    int signo;
    sscanf(argv[1], "%d", &signo);
    
    pid_t pid;
    for(int i=2; i < argc; i++) {

        sscanf(argv[i], "%d", &pid); 

        if (kill(pid, signo) == -1) {
            error(0, errno, "kill(%d, %d)", pid, signo);
        }
    }
    return 0;
}
