#include <func.h> 
#define BUFFER_SIZE 8192
//[200~'wc' (word count)是Unix下的一个工具, 
//它可以统计一个文本文件中字符的个数(也统计不可打印字符和空白字符)，
//单词的个数 (单词与单词之间以空白字符分隔) 以及行数。
//请实现一个 'wc' 程序，当传入的参数个数不对时，请给出提示信息。
//
//// 使用方式：./wc file
//// argc的值应该为2
typedef struct Scanner{
    int word_counter;
    int character_counter;
    int line_counter;
    char* previous;
    char* current;
}Scanner;

Scanner scanner;
//特殊处理让指针一开始指向一个空字符，避免文件开头是空白字符
char c=' ';


void init_scanner(char* fp){
    scanner.word_counter=0;
    scanner.character_counter=0;
    scanner.line_counter=0;
    scanner.previous=&c;
    scanner.current=fp;
}

char advance(){
    // 每调用一次advance()字符数加1
    scanner.character_counter++;
    scanner.previous=scanner.current;
    return *scanner.current++;
}

char peek(){
    return *scanner.current;
}

char peek_pre(){
    return *scanner.previous;
}

bool is_blank(char c){
    if(c == ' ' || c == '\t' || c == '\n' || c == '\r'){
        return true;
    }
    return false;
}

void scan(){
    for(;;){
        if(is_blank(peek())){
            //如果当前是空格，上一个不是空格，则单词数加1
            if(!is_blank(peek_pre())){
               scanner.word_counter++; 
            }
            if(advance()== '\n'){
                scanner.line_counter++;
              }
        }else{
            if(peek()=='\0') {
                return;
            }
            //当前处理的字符不是空格,也不是文件结尾
            advance();
        }
    }
}

char* read_file(const char* path) {
    FILE *src_fp = fopen(path,"rb");
    if(!src_fp){
        perror("fopen src");
        exit(1);
    }
    //将文件指针移到末尾
    fseek(src_fp,0L,SEEK_END);
    long file_size = ftell(src_fp);
    rewind(src_fp);
    //申请相应大小的动态内存空间，并为’\0’预留一个字符单位空间
    char* buffer = (char*) malloc(sizeof(char)*(file_size+1));
    if (buffer == NULL){
        fprintf(stderr, "malloc failed in read file.\n");
        fclose(src_fp);
        return NULL;
    }
    fread(buffer,1,file_size,src_fp);
    buffer[file_size] = '\0';
    fclose(src_fp);
    return buffer;
}

void print_result(){
    printf("line_num is %d\n",scanner.line_counter);
    printf("word_num is %d\n",scanner.word_counter);
    printf("character_counter is %d\n",scanner.character_counter);
}

int main(int argc, char* argv[])
{

    if(argc!=2){
        fprintf(stderr,"args error!\n");
        exit(1);
    }

    char* fp = read_file(argv[1]);
    init_scanner(fp);
    scan();
    print_result();

    return 0;
}

