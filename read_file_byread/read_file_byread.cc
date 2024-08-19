#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "usage: program_name file_name" << endl;
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[1]);

    // 获取文件长度
    ifs.seekg(0, std::ios::end);
    std::streamsize file_len = ifs.tellg();

    // 将游标置回文件开头
    ifs.seekg(0);

    // 申请一个字符数组用来存储文件内容
    char* buff = new char[file_len + 1]();

    ifs.read(buff, file_len);

    std::string content(buff);
    cout<< content << endl;
    
    delete[] buff;
    ifs.close();
    return 0;
}

