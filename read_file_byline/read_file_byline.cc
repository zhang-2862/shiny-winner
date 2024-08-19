#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using std::cout;
using std::endl;

void getline_like_c(std::ifstream& ifs) {
    char buff[1024];

    while (ifs.getline(buff, sizeof(buff))) {
        cout << buff << endl;
        memset(buff, 0, sizeof(buff));
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "usage: program_name file_name" << endl;
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[1]);

    // 用兼容c语言的方式读取文件
    getline_like_c(ifs);
        // 检查文件流状态

    // 清除文件流的fail状态，此时进入fail状态是因为读完文件所有内容后
    // getline的最后一次调用会失败
    if (ifs.fail()) {
        cout << "File stream is in fail state." << endl;
        ifs.clear(); // Clear error flags
    }

    // 将文件流游标初始化到文件头处
    ifs.seekg(0, std::ios::beg);

    cout << "第二次读取文件" << endl;


    std::string line;

    while (getline(ifs, line)) {
        cout << line << endl;
    }

    ifs.close();
    
    return 0;
}

