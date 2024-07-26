#ifndef __process_pool_H
#define __process_pool_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <error.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/uio.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

typedef void (*sighandler_t)(int);

#define ARGS_CHECK(argc, num)   {\
    if(argc != num){\
        fprintf(stderr, "ARGS ERROR!\n");\
        return -1;\
    }}

#define ERROR_CHECK(ret, num, msg) {\
    if(ret == num) {\
        perror(msg);\
        return -1;\
    }}

// 线程的状态
typedef enum {
    FREE,
    BUSY
} status_t;

typedef struct {
    pid_t pid; // 子进程的id
    int pipefd; // 与子进程通信的管道
    status_t status; // 0 空闲，1是忙碌
} process_data;

int makechild(process_data* ,int);
int do_task(int pipefd);

int send_fd(int pipefd, int fd);
int recv_fd(int pipefd, int* fd);

int tcp_init(const char* ip, unsigned short port);
int epoll_add_rdevent(int epfd, int fd);
int epoll_del_rdevent(int epfd, int fd);

#endif

