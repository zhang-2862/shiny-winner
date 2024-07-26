#include <func.h>

/* created on ...       */

int sendFd(int pipefd, int fd) {
    // 构建第二组成员
    char buff[1] = {0};
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buff;
    iov.iov_len = sizeof(buff);

    //构建第三组成员
    int len = CMSG_LEN(sizeof(fd));
    struct cmsghdr* pcmsg = (struct cmsghdr*)calloc(1, len);
    pcmsg->cmsg_len = len;
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    int* p = (int*)CMSG_DATA(pcmsg);
    *p = fd;

    // 构建msghdr
    struct msghdr msg;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = pcmsg;
    msg.msg_controllen = len;

    sendmsg(pipefd, &msg, 0);
    
    return 0;
}
