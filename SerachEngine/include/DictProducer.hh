#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include "SplitTool.hh"

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

    void bulidEnDict(); // 创建英文字典
    void bulidCnDict(); // 创建中文字典
    void storeDict(const char* filepath); // 将词典写入文件

private:
    vector<string> files_; // 语料库文件的绝对路径
    vector<pair<string, int>> dict_; // 词典
    SplitTool* splitTool; // 分词工具
    map<string, set<int>> index_; // 词典索引
};

#endif

