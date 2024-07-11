#include <func.h>

char* new_env[] = {"user= zg", "aaa=hello", NULL};
char* args[] = {"./echoall", "aaa", "bbb", "ccc", NULL};

int main(int argc, char* argv[])
{
    printf("BEGIN\n");
    
     execlp("echoall", "./echoall", "hello", "world", NULL);
    // execl("echoall", "./echoall", "hello", "world", NULL);
    // execle("echoall", "./echoall", "hello", "world", NULL, new_env);
    // execve("echoall", args, new_env);
    printf("you can't see me, END\n");
    return 0;
}

