#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <unordered_map>
#include <sstream>
#include <chrono>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::unordered_map;


class Dictionary
{
public:
	//......
    Dictionary();
    void read(const std::string &filename);
    void store(const std::string &filename);
private:
    bool isValidWord(string word) const;
private:
    unordered_map<string, int> word_map;
};

Dictionary::Dictionary() {}

bool Dictionary::isValidWord(string word) const {
    for (const auto& e : word) {
        if (std::isalpha(e) == 0) {
            return false;
        }
    }
    return true;
}

void Dictionary::read(const string& filename) {
    cout << "start read." << endl;
    std::ifstream ifs(filename);
    if (!ifs) {
        cout << "ifs open file fail" << endl;
    }

    string line;
    string word;
    while (getline(ifs, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
                // 不是单词则跳过
            if (!isValidWord(word)) {
                continue;
            }
            ++word_map[word];
        }
    }
    ifs.close();
    cout << "read over." << endl;
}

void Dictionary::store(const std::string &filename) {
    cout << "start store." << endl;
    std::ofstream ofs(filename, std::ios::app);

    for (auto& e : word_map){
        ofs << e.first << " " << e.second << endl;
    }
    cout << "store over." << endl;

    ofs.close();
}


int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    /* time_t start_t= time(NULL); */
    if (argc < 2) {
        cerr << "usage: input_file output_file";
    }

    Dictionary dic;
    dic.read(argv[1]);
    dic.store(argv[2]);

    /* time_t end_t= time(NULL); */
    auto stop =  std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    cout << "运行时间：" << duration << endl;
    return 0;
}

