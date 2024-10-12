#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include "SplitTool.hh"
#include "DirScanner.hh"

#include <set>
#include <map>
#include <utility>

using std::pair;
using std::set;
using std::map;

class DictProducer {
public:
    DictProducer(const string& dir);
    DictProducer(const string& dir, SplitTool* splitTool); // 专为中文处理
    ~DictProducer();

    void buildEnDict(); // 创建英文字典
    void buildCnDict(); // 创建中文字典
    void buildEnIndex(); // 创建英文字典索引
    void buildCnIndex(); // 创建中文字典索引
    void storeDict(const char* filepath); // 将词典写入文件
    void storeIndex(const char* filepath); // 将词典索引写入文件
                                           
    // 仅供测试
    void printIndex() {
        for (const auto& e : index_) {
            cout << e.first << " ";
            for (const auto& i : e.second) {
                cout << i << " ";
            }
            cout << "\n";
        }
    }
    void printDict() {
        for (const auto& e : dict_) {
            cout << e.first << " " << e.second << "\n";
        }
    }
private:
    void clear(string& word); //清洗非字母数据

private:
    vector<string> en_files_; // 英文语料库文件的绝对路径
    vector<string> cn_files_; // 语料库文件的绝对路径集合
    vector<pair<string, int>> dict_; // 词典
    SplitTool* splitTool; // 分词工具
    map<string, set<int>> index_; // 词典索引
    DirScanner dirScanner_; // 用来扫描目录中的文件
};

#endif

