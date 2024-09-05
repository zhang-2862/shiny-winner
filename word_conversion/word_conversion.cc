#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

using std::cout;
using std::endl;
using std::unordered_map;
using std::string;

class WordConverter{
public:
    void ConversionTxt(const string& map_filename, const string& txt) {
        ReadMap(map_filename);

        std::ifstream ifs(txt);
        if (!ifs) {
            perror("txt open failed.");
        }

        std::ofstream ofs("outfile"); // 用来存储转换后的文档
        if (!ofs) {
            perror("out.txt open failed");
        }

        string line; // 暂存读入的行
        string word;
        while (getline(ifs, line)) {
            std::istringstream iss(line);
            while (iss >> word) {
                cout << "conversion..." << endl;
                auto ret = word_map_.find(word);
                // 若在map中查找到单词则替换并写入out文件、否则直接写入
                if (ret != word_map_.end()) {
                    ofs << ret->second;
                } else {
                    ofs << word;
                }
                // 每写入一个单词在词尾添加一个空格
                ofs << ' ';
            }
            // 每写入一行 在行尾写入一个换行符
            ofs << '\n';
        }
    }

private:
    // 读map文件
    void ReadMap(const string& map_filename) {
        std::ifstream ifs(map_filename);
        if (!ifs) {
            perror("open map failed");
        }

        string line;
        string key;
        string value;
        while (getline(ifs, line)) {
            cout << "parse..." << endl;
            std::istringstream iss(line);
            while (iss >> key >> value) {
                word_map_.insert({key,value});
            }
        }
    }

private:
    unordered_map<string,string> word_map_;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("usage: map.txt file.txt");
        return EXIT_FAILURE;
    }
    WordConverter().ConversionTxt(argv[1], argv[2]);

    return 0;
}

