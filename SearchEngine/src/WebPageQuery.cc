#include "WebPageQuery.hh"
#include "SplitTool.hh"
#include "Configuration.hh"
#include "nlohmann/json.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <queue>

using std::ifstream;
using std::istringstream;
using std::cerr;
using std::priority_queue;


WebPageQuery::WebPageQuery(SplitTool * wordCutTool)
    : wordCutTool_(wordCutTool)
{
    init();
}

string WebPageQuery::doQuery(const string& str) {
    vector<string> words{processSentence(str)};
    if (words.size() == 0) { // 去除停用词后判断是否为空
        return "";// 无效查询，直接返回空串
    }
    set<int> webset; // 接收网页结果集
    if (!isWebExist(words, webset)) {
        return ""; // 目标网页不存在
    }
    // 计算words向量
    auto wordsFeatureVector = getWordsFeatureVector(words);
    vector<double> sentence_vec; //用于记录sentence的特征向量
    for (const auto& e : wordsFeatureVector) {
        sentence_vec.push_back(e.second);
    }
    // 获取webset的排序后的结果集
    set<pair<double, int>> result_set;// double为余弦相似度，int为网页编号
    for (const auto& e : webset) {
        vector<double> vec; //用于记录web的特征向量
        for (const auto& pair : wordsFeatureVector) {
            vec.push_back(invertIndexLib_[pair.first][e]);

        }
        double similarity = getSimilarity(sentence_vec, vec);
        result_set.insert({similarity, e});
    }
    return getResultWebPage(result_set);
}

string WebPageQuery::getResultWebPage(set<pair<double, int>>& webset) {
    // json序列化 所有网页
    nlohmann::json jsonObject;
    auto configMap = Configuration::getInstance()->configMap();
    string newripepage_path = configMap["newripepage_PATH"];

    ifstream newripepage(newripepage_path);
    if (!newripepage) {
        cerr << "getResultWebPage: newripepage open failed\n";
    }
    // 根据web编号获取所有网页查询结果
    int docid;
    int pos;
    int length;
    const size_t buffer_size = 1024 * 1024;// 1MB
    vector<char> buff(buffer_size);
    WebPage webPage;
    int idx = 0;
    for (const auto& e : webset) {
        docid = e.second;
        pos = offsetLib_[docid].first;
        length = offsetLib_[docid].second;
        newripepage.seekg(pos);
        newripepage.read(buff.data(), length);

        string doc(buff.data(), length);
        jsonObject[idx++] = doc;
    }
    return jsonObject.dump();
}

double WebPageQuery::getSimilarity(vector<double> lhs, vector<double> rhs) {
    double dot_product = 0;
    double lhs_SumOfSuqare = 0;
    double rhs_SumOfSuqare = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        dot_product += lhs[i] * rhs[i];
        lhs_SumOfSuqare += lhs[i] * lhs[i];
    }
    for (size_t i = 0; i < rhs.size(); ++i) {
        rhs_SumOfSuqare += rhs[i] * rhs[i];
    }
    return dot_product / (sqrt(lhs_SumOfSuqare) * (sqrt(rhs_SumOfSuqare)));
}


vector<pair<string, double>> 
    WebPageQuery::getWordsFeatureVector(vector<string> words) {
    unordered_map<string, int> TF_map; // 记录TF 某个词在句子中出现次数        
    for (const auto& word : words) {
        ++TF_map[word];
    }
    int N = offsetLib_.size(); // 文档总数
    double DF; // 某词在所有文章中出现的次数  
    double IDF; //逆文档频率
    double weight; // 权重
    double sumOfSquareWeight = 0.0; // 权重平方和
    vector<pair<string, double>> pairsOf_WordWeight;
    for (const auto& word : words) {
        DF = invertIndexLib_[word].size();
        IDF = log2(N / (DF + 1) + 1);
        weight = IDF * TF_map[word];
        sumOfSquareWeight += weight * weight;
        pairsOf_WordWeight.push_back({word, weight});
    }
    // 进行权重归一化
    for (auto& e : pairsOf_WordWeight) {
        weight = e.second;
        e.second = weight / sqrt(sumOfSquareWeight);
    }
    return pairsOf_WordWeight;
}


vector<string> WebPageQuery::processSentence(const string& str) {
    set<string> stoplist = Configuration::getInstance()->stopWorldList();
    vector<string> words = wordCutTool_->cut(str);
    vector<string> result;
    for (const auto& word : words) {
        if (stoplist.count(word) == 0) {
            result.push_back(word);
        }
    }
    return result;
}

bool WebPageQuery::isWebExist(vector<string> words, set<int>& webset) {
    if (words.size() == 1) { // 如果只有一个查询词
        return true;
    } else if (words.size() == 0) {
        return false;
    }
    vector<set<int>> wordsets; // 用来存包含word的文章集合
    for (const auto& word : words) {
            auto index = invertIndexLib_[word];
            set<int> tmp; // 存储每个word对应的文章id
            for (const auto& e : index) { // 遍历索引
                tmp.insert(e.first);
            }
            wordsets.emplace_back(std::move(tmp));
        }
     webset = getItersection(wordsets);
     return webset.size();
}

// 需要确保传入的wordsets大于1，否则无意义
set<int> WebPageQuery::getItersection(vector<set<int>>& wordsets) {
    // 初始交集为第一个集合
    std::set<int> intersection_result = wordsets[0];

    // 临时存放结果的容器
    std::set<int> temp_result;

    // 对所有 wordsets 求交集
    for (size_t i = 1; i < wordsets.size(); ++i) {
        // 临时存储每次的交集
        temp_result.clear();

        // 计算 intersection_result 与 wordsets[i] 的交集
        set_intersection(intersection_result.begin(), intersection_result.end(),
                              wordsets[i].begin(), wordsets[i].end(),
                              inserter(temp_result, temp_result.begin()));

        // 更新 intersection_result
        intersection_result = temp_result;

        // 如果某次交集为空，提前退出循环
        if (intersection_result.empty()) {
            break;
        }
    }
    return intersection_result;
}

void WebPageQuery::init() {
    map<string, string> configMap = Configuration::getInstance()->configMap();
    string offsetLib_path = configMap["newoffset_PATH"];
    string invetIndex_path = configMap["invetIndex_PATH"];

    // 读取偏移库
    ifstream offsetLib(offsetLib_path);
    if (!offsetLib) {
        cerr << "init: offsetLib open failed\n";
    }
    string line;
    int docid;
    int pos;
    int length;
    while (getline(offsetLib, line)) {
        istringstream iss(line);
        iss >> docid >> pos >> length;
        offsetLib_[docid] = {pos, length};
    }

    // 读取倒排索引库
    ifstream invertIndexLib(invetIndex_path);
    if (!invertIndexLib) {
        cerr << "init: invetIndexLib open failed\n";
    }
    string word;
    double weight; // 单词权重
    while (getline(invertIndexLib, line)) {
        istringstream iss(line);
        iss >> word;
        while (iss >> docid >> weight) {
            invertIndexLib_[word][docid] = weight;
        }
    }
}

