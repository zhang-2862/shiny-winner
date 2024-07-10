#include <func.h>
int main(int argc, char* argv[])
{
    if(argc !=3){
        error(1,0,"Usage: %s dst_file,%s src_file",argv[1],argv[2]);
    }
    
    int fd_w =open(argv[1],O_RDWR | O_CREAT |O_TRUNC,0666);
    if(fd_w == -1){
        error(1,errno,"open %s",argv[1]);

    }
    int fd_r = open(argv[2],O_RDONLY);
    if(fd_r == -1){
        error(1,errno,"oepn %s",argv[2]);
    }
    char buf[1024];
    ssize_t sret= read(fd_r,buf,sizeof(buf));

    write(fd_w,buf,sret);

    close(fd_r);
    close(fd_w);
    return 0;
}

