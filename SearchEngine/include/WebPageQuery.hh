#ifndef __WEBPAGEQUERY_H__
#define __WEBPAGEQUERY_H__

#include "WebPage.hh"

#include<utility>
#include <unordered_map>
#include <vector>
#include <set>
#include <map>

using std::pair;
using std::unordered_map;
using std::vector;
using std::set;

class SplitTool;

class WebPageQuery {
public:
    WebPageQuery(SplitTool* wordCutTool);
    string doQuery(const string& str);

private: 
    string getResultWebPage(set<pair<double, int>>& webset);
    double getSimilarity(vector<double> lhs, vector<double> rhs); // 获取余弦相似度
    // 获取句子的特征向量
    vector<pair<string, double>> getWordsFeatureVector(vector<string> words);
    vector<string> processSentence(const string& str); // 对句子进行分词
    //判断web是否存在,并获取网页集
    bool isWebExist(vector<string> words, set<int>& webset); 
    set<int> getItersection(vector<set<int>>& wordsets);
    void init();

private:
    SplitTool* wordCutTool_;
    vector<WebPage> pages_;
    unordered_map<int, pair<int, int>> offsetLib_;
    unordered_map<string, unordered_map<int, double>> invertIndexLib_;
};

#endif

