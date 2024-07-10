#include <func.h>

int main(int argc, char* argv[])
{
    if(argc!=2){
        error(1,0,"Usage: filename");
    }
    int fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC,0666);
    if(fd == -1) {
        error(1,errno,"open %s",argv[1]);
    }
    if(ftruncate(fd,40959) == -1) {
        error(1,errno, "ftruncate %d", fd);
    }
    off_t ret =  lseek(fd, 0L, SEEK_END);
    if(ret == -1) {
        error(1, errno, "seek failed");    
    }
    if(write(fd, "Hello world",11) == -1) {
        error(1, errno, "write failed");
    }
    struct stat status;
    if(fstat(fd, &status)) {
        error(1, errno, "get fstat failed");
    }
    
    printf("blocks: %ld ino: %ld size: %ld mode: %lo nlink: %ld ",
           status.st_blocks,
           status.st_ino,
           status.st_size,
           (long)status.st_mode,
           status.st_nlink);
    return 0;
}

