#include "DictProducer.hh"
#include "Configuration.hh"
#include "SplitToolCppJieba.hh"
#include "DirScanner.hh"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::cerr;
using std::multiset;
using std::ios;

DictProducer::DictProducer(const string& en_dir, const string& cn_dir, SplitTool* SplitTool) {
    dict_.reserve(53000); //经测试后大概有53000个单词，给vector预留空间加速生成词典
    DirScanner cn_scanner; //扫描文件夹中所有文件并存入扫描器
    DirScanner en_scanner;

    en_scanner(en_dir);
    en_files_ = en_scanner.files();

    cn_scanner(cn_dir);
    cn_files_ = cn_scanner.files();

    buildEnDict();// 创建英文词典
    buildCnDict(SplitTool); // 创建中文词典
    buildIndex(); // 创建索引
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

void DictProducer::buildCnDict(SplitTool* splitTool) {
    map<string, int> dict_map; // 临时哈希
    set<string> stoplist = Configuration::getInstance()->stopWorldList(); // 停用词列表
    
    for (auto& file : cn_files_) {
        ifstream ifs(file);
        if (!ifs) {
            cerr << "openCndict file fail\n";
            return;
        }

        string line;
        string txt;  // 用于存储整个清洗后的文件内容

        // 逐行读取文件内容，清除 \r 和 \n
        while (std::getline(ifs, line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());  // 清除 \r
            txt += line;  // 将清洗后的内容追加到 txt
        }
        ifs.close();  // 关闭文件

        // 使用分词工具对清洗后的文本进行分词
        vector<string> tmp = splitTool->cut(txt);
        for (auto& word : tmp) {
            // 如果不是停用词，并且UTF-8字节数为3，统计词频
            if (!stoplist.count(word) && getByteNum_UTF8(word[0]) == 3) {
                ++dict_map[word];
            }
        }
    }

    // 将map中的内容存储到dict_中
    copy(dict_map.begin(), dict_map.end(), back_inserter(dict_));
}


/* void DictProducer::buildEnIndex() { */
/*     cout << "buildEnIndex...\n"; */
/*     for (size_t i = 0; i < dict_.size(); ++i) { */
/*         string word = dict_[i].first; */
/*         for (const auto& e : word) { // 对单词的每个单字进行处理 */
/*             // 遍历词典中所有的单词将包含该单字的索引加入map对应的set中 */
/*             string str(1, e); */
/*             index_[str].insert(i); */
/*         } */
/*     } */
/*     cout << "buildEnIndex    end...\n"; */
/* } */

void DictProducer::buildIndex() {
    int i = 0; // 记录下标
    for (auto elem : dict_) {
        string word = elem.first;
        // 得到字符数
        size_t charNums = word.size() / getByteNum_UTF8(word[0]);
        for (size_t idx = 0, n = 0; n != charNums; ++idx, ++n) { 
            // 按照字符数进行切割
            size_t charLen = getByteNum_UTF8(word[idx]);
            string subword = word.substr(idx, charLen); //按照编码格式，进行拆分
            index_[subword].insert(i);
            idx += (charLen - 1);
        }
        ++i;
    }
}

void DictProducer::storeDict(const char* filepath) {
    ofstream ofs(filepath);
    cout << "storeDict open file...\n";
    if (!ofs) {
        cerr << "Failed to open file: " << filepath << endl;
        return;
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

size_t DictProducer::getByteNum_UTF8(const char byte) {
    int byteNum = 0;
    for (size_t i = 0; i < 6; ++i) {
        if (byte & (1 << (7 - i))) {
            ++byteNum;
        } else {
            break;
        }
    }
    return byteNum == 0 ? 1 : byteNum;
}

