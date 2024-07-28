#include "processPool.h"

int makechild(process_data * p_process, int num) {
    for(int i = 0; i < num; ++i) {
        int fds[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, &fds);
        pid_t pid = fork();
        if (pid == 0) {
            close(fds[1]);
            // 子进程执行任务
            do_task(fds[0]);
            exit(0);
        }
        // 父进程
        close(fds[0]);
        // 记录子进程的信息
        p_process[i].pid = pid;
        p_process[i].pipefd = fds[1]; // 与父进程通信的管道
        p_process[i].status = FREE;
    }

    return 0;
}
