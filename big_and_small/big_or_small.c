#include "func.h"

int main(int agrc, char* argv[]) {
    int i = 0x12345678;
    char* p = &i;
    printf("%x\n", *p);
    return 0;
}

