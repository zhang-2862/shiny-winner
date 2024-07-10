#include <func.h>

int main(int argc, char* argv[])
{
    char* cwd = getcwd(NULL, 0);
    ERROR_CHECK(cwd, NULL, "getcwd");
    puts(cwd);
    free(cwd);
    printf("Hello world\n");
    return 0;
}

