#include "Dictionary.hh"
#include "Configuration.hh"

#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::istringstream;
using std::cerr;

Dictionary* Dictionary::dic_instance_ = nullptr;
Dictionary::AutoRelease Dictionary::ar_;

Dictionary* Dictionary::getInstance() {
    if (dic_instance_ == nullptr) {
        dic_instance_ = new Dictionary();
        string dict_path = Configuration::getInstance()->configMap()["dict_PATH"];
        string index_path = Configuration::getInstance()->configMap()["dictIndex_PATH"];
        dic_instance_->init(dict_path, index_path);
    }
    return dic_instance_;
}

vector<pair<string, int>> Dictionary::doQuery(const string& str) {
    vector<pair<string, int>> res; //把相关词集存储
    
    // TODO 根据单字查询所有相关词
    set<int> word_set = index_[word];    
    for (const auto& e : word_set) { // 按照行号查相关词放入词集
        res.push_back(dict_[e]);
    }
    return res;
}

void Dictionary::init(string dict_path, string index_path) {
    ifstream dict(dict_path);
    if (!dict) {
        cerr << "dict open failed\n";
    }
    string line;
    string word; // 单词
    int frequence; // 词频
    while (getline(dict, line)) {
        istringstream iss(line);
        iss >> word >> frequence;
        dict_.push_back({word, frequence});
    }

    int row; // 行号
    ifstream index(index_path);
    if (!index) {
        cerr << "index open failed\n";
    }
    while (getline(index, line)) {
        istringstream iss(line);
        iss >> word;
        while (iss >> row) {
            index_[word].insert(row);
        }
    }
}

vector<string> Dictionary::getWord(const string& str) { // 获取分字
    vector<string> res;
    for (size_t i = 0; i < str.size();) {
        char ch = str[i];
        size_t codeLength = nBytesCode(ch); //获取编码长度
        res.push_back(str.substr(i, codeLength));
        i += codeLength;
    }
    return res;
}

size_t Dictionary::nBytesCode(const char ch) { // 获取整个字的字符长度
    if (ch & (1 << 7)) {
        int nBytes = 1;
        for (int idx = 0; idx != 6; ++idx) {
            if (ch & (1 << (6 - idx))) {
                ++nBytes;
            } else {
                break;
            }
        }
        return nBytes;
    }
    return 1;
}
