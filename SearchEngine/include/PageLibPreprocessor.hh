#ifndef __PAGELIBPREPROCESSOR_H__
#define __PAGELIBPREPROCESSOR_H__

#include "simhash/Simhasher.hpp"

#include <utility>
#include <unordered_map>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>

using std::pair;
using std::unordered_map;
using std::vector;
using std::string;
using std::map;
using std::set;
using std::cout;

class SplitTool;

class PageLibPreprocessor {
    // 用于存储每篇文章中的词频统计
    using WordCountPerDoc = unordered_map<string, int>;
public:
    PageLibPreprocessor(SplitTool* splitTool);

    void buildInvetIndexTable(); //创建倒排索引表
    void StoreOnDisk(); // 将经过处理之后的位置偏移库和倒排索引表写回到磁盘上
    // 仅供测试
    void printOffsetLib() {
        for (const auto& e : offsetLib_) {
            cout << e.first << " " << e.second.first
                 << " " << e.second.second << "\n";
        }
    }
    void printDF_map() {
        for (const auto& e : DF_map_) {
            cout << e.first;
            for (const auto& ele : e.second) {
                cout << " " << ele;
            }
            cout << "\n";
        }
    }
private: 
    void processWebs(); // 根据配置信息读取网页库和位置偏移库的内容进行去重
    void getSimhash(const string& content, size_t top_n, uint64_t& u64);
    bool isUnique(vector<uint64_t>& vec, uint64_t);// 用来判断网页是否重复
    // 计算某单词在某篇文章中的逆文档频率
    double calculateWeight(const string& word, int doc_id);
    void processDocument(int docId, const string& content);

private:
    SplitTool* wordCutter_; // 分词对象
    unordered_map<int, pair<int,int>> offsetLib_; // 网页偏移库对象
    unordered_map<string, vector<pair<int, double>>> invertIndexTable_; // 倒排索引表对象
    map<string, string> configMap_; //配置文件map
    simhash::Simhasher simhasher_; //simhasher对象 用于求网页的哈希值
    int doc_count_; // 文章总数
    unordered_map<string, set<int>> DF_map_; // 计算出现某单词的文章数
    unordered_map<int, WordCountPerDoc> TF_map_; // 文档编号 -> (单词->该文档中出现次数)
};

#endif

