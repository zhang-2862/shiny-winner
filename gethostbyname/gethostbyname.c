#include "func.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        error(1, 0, "agrc == 2");
    }

    struct hostent* pHost = gethostbyname(argv[1]);
    if (pHost != NULL) {
        //打印官方的主机信息
        printf("host name: %s\n", pHost->h_name);
        // 打印官方别名信息
        for (int i = 0; pHost->h_aliases[i] != NULL; ++i) {
            printf("aliases[%d]: %s\n", i, pHost->h_aliases[i]);
        }
        printf("addrtype: %d\n", pHost->h_addrtype);
        printf("length: %d\n", pHost->h_length);

        //打印ip地址
        for (int i = 0; pHost->h_addr_list[i] != NULL; ++i) {
            char buff[64];
            inet_ntop(pHost->h_addrtype,
                      pHost->h_addr_list[i],
                      buff, sizeof(buff));
            printf("addr[%d]: %s\n", i, buff);
        }
    }


    return 0;
}

