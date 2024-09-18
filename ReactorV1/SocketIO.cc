#include "SocketIO.hh"

#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>


SocketIO::SocketIO(int fd)
    : fd_(fd)
{

}
SocketIO::~SocketIO() {

}

int SocketIO::readn(char* buf, int len) {
    int left = len;
    char* ptr = buf;

    while (left > 0) {
        int nByte = read(fd_, ptr, left);
        if (nByte == -1 && errno == EINTR) {
            continue;
        } else if (nByte == -1) {
            perror("readn error");
            return -1;
        } else if (nByte == 0){
            break;
        } else {
            left -= nByte;
            ptr += nByte;
        }
    }
    return len - left;
}

int SocketIO::writen(const char* buf, int len) {
    int left = len;
    const char* ptr = buf;

    while (left > 0) {
        int nByte = write(fd_, ptr, left);
        if (nByte == -1 && errno == EINTR) {
            continue;
        } else if (nByte == -1) {
            perror("writen error");
            return -1;
        } else if (nByte == 0){
            break;
        } else {
            left -= nByte;
            ptr += nByte;
        }
    }
    return len - left;
} 

int SocketIO::readLine(char* buf, int len) {
    int left = len - 1;
    char* ptr = buf;
    int total = 0;

    while (left > 0) {
        int nByte = recv(fd_, ptr, left, MSG_PEEK);
        if (nByte == -1 && errno == EINTR) {
            continue;
        } else if (nByte == -1) {
            perror("readLine error");
            return -1;
        } else if (nByte == 0){
            break;
        } else {
            for (int idx = 0; idx < nByte; ++idx) {
                if (ptr[idx] == '\n') {
                    // 遍历到换行符,说明前面为一行内容
                    int rz = idx + 1;
                    readn(ptr, rz);
                    ptr += rz;
                    *ptr = '\0';// 在末尾添加结束符

                    return total + rz;
                }
            }
            readn(ptr, nByte);
            left -= nByte;
            ptr += nByte;
            total += nByte;
        }
    }
    *ptr = '\0';

    return len - total;
    /* return total - left; */
}
