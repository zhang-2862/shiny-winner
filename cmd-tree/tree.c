#include <func.h>

//写一个小程序，实现青春版 tree 命令。效果如下：
//
//$ ./tree .
//.
//	dir1
//		text1
//		text2
//	dir2
//		file1
//		file2
//	dir3
//		a.txt
//		b.txt
//
//3 directories, 6 files

// tree.c
void dfs_print(const char* path, int width);	/* width: 缩进的空格数目 */

int directories = 0, files = 0;

int main(int argc, char *argv[])
{
    // ./tree dir
    ARGS_CHECK(argc, 2);

    puts(argv[1]);		// 打印目录的名字

    dfs_print(argv[1], 4);	// 递归打印每一个目录项

    printf("\n%d directories, %d files\n", directories, files);		// 最后打印统计信息
                                                                    
    return 0;
}

void dfs_print(const char* path, int width) {
    DIR* stream = opendir(path);
    ERROR_CHECK(stream, NULL , "opendir");
    
    errno = 0;
    struct dirent* p;
    while((p=readdir(stream))!=NULL){
        const char* name = p->d_name;
        if(strcmp(name,".")==0 || strcmp(name,"..")==0){
            continue;
        }
        for(int i=0; i<width; i++){
            putchar(' ');
        }
        puts(name);
        if(p->d_type==DT_DIR){
            directories++;
            char subpath[256];
            sprintf(subpath,"%s/%s",path,name);
            dfs_print(subpath,width+4);
        }else if(p->d_type == DT_REG){
            files++;
        }
    }
        if(errno){
            error(0,errno,"readdir");
        }
        closedir(stream);
    
}	/* width: 缩进的空格数目 */

