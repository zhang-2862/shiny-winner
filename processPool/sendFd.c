#include <func.h>

/* created on ...       */

int send_fd(int pipefd, int fd) {
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

int recv_fd(int pipefd, int* pfd) {
    // 构建第二组成员
    char buff[1] = {0};
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buff;
    iov.iov_len = sizeof(buff);

    //构建第三组成员
    int len = CMSG_LEN(sizeof(int));
    struct cmsghdr* pcmsg = (struct cmsghdr*)calloc(1, len);
    pcmsg->cmsg_len = len;
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    //构建一个 struct msghdr
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = pcmsg;
    msg.msg_controllen = len;

    int ret = recvmsg(pipefd, &msg, 0);
    ERROR_CHECK(ret, -1, "recvmsg");
    int* p =(int*)CMSG_DATA(pcmsg);
    *pfd = *p; // 读取文件描述符的值，并传给外界的变量
    
    return 0;
}
