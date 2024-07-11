#include <func.h>

void atexitFunc1(void) {
    printf("atexitFunc1 is called.\n");
}

void atexitFunc2(void) {
    printf("atexitFunc2 is called.\n");
}

void onexitFunc1(int status, void* args) {
    printf("onexitFunc1 is called, status is %d print %ld.\n",status,(long)args);
}

void onexitFunc2(int status, void* args) {
    printf("onexitFunc2 is called, status is %d print %ld.\n",status,(long)args);
}

int main(int argc, char* argv[])
{
    if (atexit(atexitFunc1) !=0) {
        error(1,0,"atexitFunc1 failed.");
    }

    if (atexit(atexitFunc2) !=0) {
        error(1,0,"atexitFunc2 failed.");
    }

    if (on_exit(onexitFunc1,(void*) 100) != 0) {
        error(1,0,"onexitFunc1 failed.");
    }

    if (on_exit(onexitFunc2,(void*) 200) != 0) {
        error(1,0,"onexitFunc2 failed.");
    }

    printf("program is runing...\n");
    return 3;
}

