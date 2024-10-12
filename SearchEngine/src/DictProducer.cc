#include "DictProducer.hh"
#include "Configuration.hh"

#include <fstream>
#include <iostream>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::cerr;
using std::multiset;

DictProducer::DictProducer(const string& dir)
{
    dirScanner_(dir); //扫描文件夹中所有文件并存入扫描器
    en_files_ = dirScanner_.files();
    buildEnDict();
    buildEnIndex();
}

DictProducer::DictProducer(const string& dir, SplitTool* SplitTool) {
    dirScanner_(dir);
    cn_files_ = dirScanner_.files();
    // TODO
}

DictProducer::~DictProducer() {

}

void DictProducer::buildEnDict() {
    map<string, int> dict_map; //临时哈希
    set<string> stoplist = Configuration::getInstance()->stopWorldList();
    multiset<string> cleaned_words; // 用于存储清洗后的单词
    
    for(auto& file : en_files_) {
        ifstream ifs(file);
        if (!ifs) {
            cerr << "ifs open file fail\n";
        }
        string line;
        string word;
        // 第一次遍历清洗单词
        while (getline(ifs, line)) {
            istringstream iss(line);
            while (iss >> word) {
                if (stoplist.find(word) != stoplist.end()) {// 跳过停用词
                    continue;
                }
                clear(word); // 清洗单词
                istringstream iss(word);
                string temp;
                while (iss >> temp) {
                    if (temp.length() > 1) {
                        cleaned_words.insert(temp);
                    }
                }
            }
        }

        for (const auto& word : cleaned_words) {
            ++dict_map[word];
        }

        ifs.close();
    }
    // 将map存储到vector中
    copy(dict_map.begin(), dict_map.end(), back_inserter(dict_));
}

void DictProducer::buildCnDict() {

}

void DictProducer::buildEnIndex() {
    cout << "buildEnIndex...\n";
    for (size_t i = 0; i < dict_.size(); ++i) {
        string word = dict_[i].first;
        for (const auto& e : word) { // 对单词的每个单字进行处理
            // 遍历词典中所有的单词将包含该单字的索引加入map对应的set中
            string str(1, e);
            index_[str].insert(i);
        }
    }
    cout << "buildEnIndex    end...\n";
}

void DictProducer::buildCnIndex() {

}

void DictProducer::storeDict(const char* filepath) {
    ofstream ofs(filepath);
    cout << "storeDict open file...\n";
    if (!ofs) {
        cerr << "Failed to open file: " << filepath << endl;
    }

    cout << "storeDict start...\n";
    
    for (const auto& entry : dict_) {
        ofs << entry.first << " " << entry.second
            << endl;
    }

    cout << "storeDict end...\n";

    ofs.close();
}

void DictProducer::storeIndex(const char* filepath) {
    std::ofstream ofs(filepath);
    cout << "storeDict open file...\n";
    if (!ofs.is_open()) {
        cerr << "Failed to open file: " << filepath << endl;
        return;
    }

    cout << "storeDict start...\n";

    for (const auto& entry : index_) {
        ofs << entry.first << " ";
        for (const auto& id : entry.second) {
            ofs << id << " ";
        }
        ofs << endl;
    }
    cout << "storeDict end...\n";

    ofs.close();
}


void DictProducer::clear(string& word) { // 将所有非字母字符替换为空格
    for (auto& e: word) {
        if (!isalpha(e)) {
            e = ' ';
        }
        e = tolower(e); //转化为小写字母
    }
}

