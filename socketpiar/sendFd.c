#include <func.h>

/* created on      */

int sendFd(int pipefd, int fd) {
    // 构建第二组成员
    char buff[1] = {0};
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buff;
    iov.iov_len = sizeof(buff);

    //构建第三组成员
    int len = CMSG_LEN(sizeof(fd));
    struct cmsghdr * pcmsg = (struct cmsghdr*)calloc(1, len);
    pcmsg->cmsg_len = len;
    pcmsg->cmsg_level =SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    int* p = (int*)CMSG_DATA(pcmsg);
    *p = fd;

    // 构建msghdr
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = pcmsg;// 传递文件描述符
    msg.msg_controllen = len;

    // sendmsg返回值大于0，则为iov传递长度
    int ret = sendmsg(pipefd, &msg, 0);
    printf("sendmsg ret: %d\n", ret);
    ERROR_CHECK(ret, -1, "sendmsg");
    free(pcmsg);
    return 0;
}

int recvFd(int pipefd, int* pfd) {
    // 构建第二组成员
    char buff[1]= {0};
    struct iovec iov;
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buff;
    iov.iov_len = sizeof(buff);

    // 构建第三组成员
    int len = CMSG_LEN(sizeof(int));
    struct cmsghdr* pcmsg = (struct cmsghdr*)calloc(1, len);
    pcmsg->cmsg_len = len;
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    // 构建一个struct msghdr
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = pcmsg;
    msg.msg_controllen = len;

    int ret = recvmsg(pipefd, &msg, 0);
    ERROR_CHECK(ret, -1, "recvmsg");
    printf("buff: %s\n", buff);
    int* p = (int*)CMSG_DATA(pcmsg);
    *pfd = *p; // 读取文件描述符

    return 0;
}
