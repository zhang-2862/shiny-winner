#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;

struct Record
{
	string _word;
	int _frequency;
    Record(const string& word, int freq)
        :_word(word),
        _frequency(freq)
    {}
};

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
    vector<Record> _dict;
};

Dictionary::Dictionary() {
    _dict.reserve(1000);
}

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

    string word;
    while (ifs >> word) {
        // 不是单词则跳过
        if (!isValidWord(word)) {
            continue;
        }
        // 遍历字典中是否已存在该单词，若存在则词频加1
        auto result = std::find_if(_dict.begin(), _dict.end(),
                           [&word](const auto& item) {return word == item._word;});
        if (result != _dict.end()) {
            ++result->_frequency;
        } else {
            _dict.emplace_back(word, 1);
        }
        /* auto it = _dict.begin(); */
        /* while ((it = _dict.begin()) != _dict.end()) { */
        /*     if (word == it->_word) { */
        /*         it->_frequency++; */
        /*         break; */
        /*     } */
        /* } */
        /* // 字典中不存在，在添加该单词 */
        /* _dict.push_back({word, 1}); */
    }
    /* for (auto& e : _dict) { */
    /*     cout << e._word << " " << e._frequency << endl; */
    /* } */

    ifs.close();
    cout << "read over." << endl;
}

void Dictionary::store(const std::string &filename) {
    cout << "start store." << endl;
    std::ofstream ofs(filename, std::ios::app);

    std::ostringstream oss;

    for (auto& e : _dict){
        oss << e._word << " " << e._frequency << endl;
        // 每拼接完一行就写入文件
        ofs << oss.str();
        oss.str(""); // 清空oss
    }
    cout << "store over." << endl;

    ofs.close();
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "usage: input_file output_file";
    }

    Dictionary dic;
    dic.read(argv[1]);
    dic.store(argv[2]);
    
    return 0;
}

