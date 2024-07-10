#include <func.h>

void copyFile(const char* src, const char* dst);
void copyDir(const char* src, const char* dst);

int main(int argc, char* argv[]) {
    // ./copyDir src dst
    ARGS_CHECK(argc, 3);
    copyDir(argv[1], argv[2]);
    return 0;
}

void copyFile(const char* src, const char* dst) {
	// 复制文件  
    FILE* src_fp=fopen(src,"r");
    if(!src_fp){
        error(1,errno,"oepn src");
    }
    FILE* dst_fp=fopen(dst,"w");
    if(!dst_fp){
        error(1,errno,"oepn dst");
    }
    char buffer[4096];
    int n;
    while((n=fread(buffer,1,1024,src_fp))>0){
        fwrite(buffer,1,n,dst_fp);
    }
    fflush(dst_fp);
    fclose(src_fp);
    fclose(dst_fp);
}

void copyDir(const char* src, const char* dst) {
    // 创建dst目录
    int ret = mkdir(dst,0775);
    ERROR_CHECK(ret,-1,"mkdir");
    // 打开src目录
    DIR* src_dir=opendir(src);
    ERROR_CHECK(src_dir,NULL,"open src dir");
    // 遍历目录流
    errno = 0;
    struct dirent* p; 
    while((p = readdir(src_dir)) != NULL) {
            const char* name = p->d_name;
             // 忽略.和.. 
            if(strcmp(name,".") == 0 || strcmp(name,"..") == 0) {
                continue;
            }
            char srcpath[256];
            char dstpath[256];
            sprintf(dstpath,"%s/%s",dst,name);
            sprintf(srcpath,"%s/%s",src,name);
        if(p->d_type == DT_DIR){
            copyDir(srcpath,dstpath);
        }else if(p->d_type == DT_REG){
            copyFile(srcpath,dstpath);
        }
        // 如果该目录项是目录，则调用copyDir递归复制
        // 如果该目录项是文件，则调用copyFile复制文件
    }
    
    if(errno){
        error(0,errno,"copy");
    }
    closedir(src_dir);
}
