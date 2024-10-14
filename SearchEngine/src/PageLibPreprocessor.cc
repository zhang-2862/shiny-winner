#include "PageLibPreprocessor.hh"
#include "Configuration.hh"
#include "WebPage.hh"
#include "SplitTool.hh"

#include <cmath>
#include <fstream>
#include <sstream>

const size_t kTopN = 15; // simhash 表示特征的数量

using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::cerr;

PageLibPreprocessor::PageLibPreprocessor(SplitTool* splitTool)
    : wordCutter_(splitTool),
      configMap_(Configuration::getInstance()->configMap()),
      simhasher_(configMap_["_conf.mapKey.DICT_PATH"],
                 configMap_["_conf.mapKey.HMM_PATH"],
                 configMap_["_conf.mapKey.IDF_PATH"],
                 configMap_["_conf.mapKey.STOP_WORD_PATH"])
{
    processWebs();
    buildMap();
}

PageLibPreprocessor::~PageLibPreprocessor() {

}

void PageLibPreprocessor::processWebs() {
    vector<uint64_t> simhashs;// 用来去重
    string offsetLib_path = configMap_["pageoffset_PATH"]; // 获取网页偏移库路径
    string ripepage_path = configMap_["ripepage_PATH"]; // 获取网页库路径
    string new_ripepage_path = configMap_["newripepage_PATH"]; // 获取去重网页库路径
    
    ifstream offset_lib(offsetLib_path);
    if (!offset_lib) {
        cerr << "processWebs: open file failed " << offsetLib_path << "\n";
    }
    ifstream page_lib(ripepage_path);
    if (!page_lib) {
        cerr << "processWebs: open file failed " << ripepage_path << "\n";
    }
    ofstream new_page_lib(new_ripepage_path);
    if (!new_page_lib) {
        cerr << "processWebs: open file failed " << new_ripepage_path << "\n";
    }

    string line;
    int doc_id;
    int doc_pos;
    int doc_length;

    int idx = 1;// 记录doc索引
    int pos = 0;// 记录doc起始位置
    int length = 0;// 记录doc长度
    // 依次获取网页
    while (getline(offset_lib, line)) { //每读取一行偏移库文件即可获取一个网页的位置信息
        istringstream iss(line);
        iss >> doc_id >> doc_pos >> doc_length;

        page_lib.seekg(doc_pos);
        char* buff = new char[doc_length + 1]();
        page_lib.read(buff, doc_length);

        string doc = buff; // 将buff转为string类型
        WebPage webPage(doc); //构建WebPage对象
        uint64_t simhash_val = 0;

        getSimhash(webPage.docContent(), kTopN, simhash_val);
        if (isUnique(simhashs, simhash_val)) {
            // 不重复的则存入newrapepage中
            pos = new_page_lib.tellp();
            new_page_lib << "<doc>\n\t<docid>" << idx 
                << "</docid>\n\t<title>" << webPage.docTitle() 
                << "</title>\n\t<link>" << webPage.docUrl() 
                << "</link>\n\t<content>" << webPage.docContent()
                << "</content>\n</doc>";
            new_page_lib << '\n';
            length = static_cast<int>(new_page_lib.tellp()) - pos;
            offsetLib_[idx++] = {pos, length};
        }
        delete[] buff;
    }
    doc_count_ = idx; // 记录文章总数
    offset_lib.close();
    page_lib.close();
}

void PageLibPreprocessor::buildMap() {
    string new_ripepage_path = configMap_["newripepage_PATH"]; // 获取新网页库路径
    
    ifstream new_page_lib(new_ripepage_path);
    if (!new_page_lib) {
        cerr << "processWebs: open file failed " << new_ripepage_path << "\n";
    }

    string line;
    int doc_id;
    int doc_pos;
    int doc_length;
    set<string> stoplist = Configuration::getInstance()->stopWorldList(); // 停用词列表

    // 依次获取网页
    for (auto& e : offsetLib_) { //offset_lib -> unordered_map<int, pair<int,int>> 
        doc_id = e.first;
        doc_pos = e.second.first;
        doc_length = e.second.second;

        char *buff = new char[doc_length + 1]();

        new_page_lib.seekg(doc_pos); // 移动文件指针
        new_page_lib.read(buff, doc_length); // 读取文件到buff中

        string doc = buff;
        WebPage webPage(doc); //构造webpage对象
        string content = webPage.docContent(); //获取网页内容
        vector<string> tmp = wordCutter_->cut(content); // 将内容进行分词
        for (const auto& word : tmp) {
            if (stoplist.count(word) == 0) { // 去停用词
                DF_map_[word].insert(doc_id);
                ++TF_map_[{word, doc_id}];
            }
        }
        delete[] buff;
    }
    new_page_lib.close();
}

void PageLibPreprocessor::buildInvetIndexTable() {
    string new_ripepage_path = configMap_["newripepage_PATH"]; // 获取新网页库路径
    
    ifstream new_page_lib(new_ripepage_path);
    if (!new_page_lib) {
        cerr << "processWebs: open file failed " << new_ripepage_path << "\n";
    }

    string line;
    int doc_id;
    int doc_pos;
    int doc_length;
    set<string> stoplist = Configuration::getInstance()->stopWorldList(); // 停用词列表

    // 依次获取网页
    for (auto& e : offsetLib_) { //offset_lib -> unordered_map<int, pair<int,int>> 
        doc_id = e.first;
        doc_pos = e.second.first;
        doc_length = e.second.second;
        double weight_squares = 0; // 记录每篇文章的单词权重平方和

        char *buff = new char[doc_length + 1]();

        new_page_lib.seekg(doc_pos); // 移动文件指针
        new_page_lib.read(buff, doc_length); // 读取文件到buff中

        string doc = buff;
        WebPage webPage(doc); //构造webpage对象
        string content = webPage.docContent(); //获取网页内容
        vector<string> tmp = wordCutter_->cut(content); // 将内容进行分词
        for (const auto& word : tmp) {
            if (stoplist.count(word) == 0) { // 去停用词
                double IDF = calculateIDF(word, doc_id);
                weight_squares += IDF * IDF;
            }
        }
        for (const auto& word : tmp) {
            if (stoplist.count(word) == 0) { // 去停用词
                double IDF = calculateIDF(word, doc_id);
                double normalized_IDF = IDF / sqrt(weight_squares);
                invertIndexTable_[word].push_back({doc_id, normalized_IDF});
            }
        }
        delete[] buff;
    }
    new_page_lib.close();
}

void PageLibPreprocessor::StoreOnDisk() {

}

void PageLibPreprocessor::getSimhash(const string& content, size_t top_n, uint64_t u64) {
    simhasher_.make(content, top_n, u64);
}

bool PageLibPreprocessor::isUnique(vector<uint64_t>& vec, uint64_t hash_val) {
    for (auto& e : vec) {
        if (simhash::Simhasher::isEqual(e, hash_val)) {
            return false;
        }
    }
    return true;
}

double PageLibPreprocessor::calculateIDF(const string& word, int doc_id) {
    int DF = DF_map_[word].size(); // 某个单词在所有文章中出现的次数
    int TF = TF_map_[{word, doc_id}];
    double IDF = log2(doc_count_ / (DF + 1) + 1);
    double weight = TF * IDF;
    return weight;
}
