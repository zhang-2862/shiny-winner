#include <func.h>
#define MMAP_SIZE 8192

int main(int argc, char* argv[])
{
    if(argc!=3){
        error(1,0,"Usage: src_file dst_file.");
    }
    int src_fd = open(argv[1],O_RDONLY);
    if(src_fd == -1){
        error(1,errno,"open %s", argv[1]);
    }
    int dst_fd = open(argv[2],O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(dst_fd == -1){
        error(1, errno, "oepn %s", argv[2]);
        close(src_fd);
    }
    
    struct stat sb;
    fstat(src_fd, &sb);
    off_t size = sb.st_size;

    ftruncate(dst_fd,size);

    off_t offset = 0;//已复制的数据大小
    
    while(offset < size){
        off_t length;
        if (size - offset >= MMAP_SIZE) {
            length = MMAP_SIZE;
        }else {
            length =size - offset;
        }
        
        void* addr1 = mmap(NULL, length, PROT_READ, MAP_SHARED, src_fd, offset);
        if (addr1 == MAP_FAILED) {
            error(1, errno, "mmap %s", argv[1]);
        }

        void* addr2 = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, offset);
        if (addr2 == MAP_FAILED){
            error(1, errno, "map %s", argv[2]);
        }
        
        memcpy(addr2, addr1, length);
        offset += length;    
        
        if(munmap(addr1,length)) {
            error(1,errno,"munmap %s",argv[1]);
        }
        if(munmap(addr2,length)) {
            error(1,errno,"munmap %s",argv[2]);
        }
    }
    close(src_fd);
    close(dst_fd);
    return 0;
}

