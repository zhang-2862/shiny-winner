#include "PageLibPreprocessor.hh"
#include "Configuration.hh"
#include "WebPage.hh"
#include "SplitTool.hh"

#include <cmath>
#include <fstream>
#include <sstream>

using std::stringstream;

const size_t kTopN = 10; // simhash 表示特征的数量

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
}

void PageLibPreprocessor::processWebs() {
    cerr << "processWebs() start...\n";

    vector<uint64_t> simhashs;// 用来去重
    string offsetLib_path = configMap_["pageoffset_PATH"]; // 获取网页偏移库路径
    string ripepage_path = configMap_["ripepage_PATH"]; // 获取网页库路径
    string new_ripepage_path = configMap_["newripepage_PATH"]; // 获取去重网页库路径
    set<string> stoplist = Configuration::getInstance()->stopWorldList(); // 停用词列表
    
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

    int idx = 0;// 记录doc索引
    int pos = 0;// 记录doc起始位置
    int length = 0;// 记录doc长度
    WebPage webPage; //构建WebPage对象
    // 使用预分配的缓冲区，假设最大文档长度为 1MB
    const size_t buffer_size = 1024 * 1024; // 1MB
    vector<char> buff(buffer_size);
    uint64_t simhash_val = 0;

    // 依次获取网页
    while (getline(offset_lib, line)) { //每读取一行偏移库文件即可获取一个网页的位置信息
        istringstream iss(line);
        iss >> doc_id >> doc_pos >> doc_length;

        cerr << "doc_id: " << doc_id << "\n";

        page_lib.seekg(doc_pos);
        page_lib.read(buff.data(), doc_length);

        string doc(buff.data(), doc_length); // 将buff转为string类型
        webPage.setDoc(doc);
        webPage.parseXml();

        getSimhash(webPage.docContent(), kTopN, simhash_val);
        if (isUnique(simhashs, simhash_val)) {
            // 不重复的则存入newrapepage中 ,并进行map统计以及
            simhashs.push_back(simhash_val);
            pos = new_page_lib.tellp();
            new_page_lib << "<doc>\n\t<docid>" << idx 
                << "</docid>\n\t<title>" << webPage.docTitle() 
                << "</title>\n\t<link>" << webPage.docUrl() 
                << "</link>\n\t<content>" << webPage.docContent()
                << "</content>\n</doc>";
            new_page_lib << '\n';
            length = static_cast<int>(new_page_lib.tellp()) - pos;
            offsetLib_[++idx] = {pos, length};
            processDocument(idx, webPage.docContent());
        }
    }
    doc_count_ = idx; // 记录文章总数
    offset_lib.close();
    page_lib.close();
}

void PageLibPreprocessor::buildInvetIndexTable() {
    for (const auto& e : TF_map_) {
        map<string, double> weightMap;// 用来记录单词在当前文章权重
        double sumofWeightSquares = 0;// 记录当前文章中的权重平方和 
        int doc_id = e.first;
        for (const auto& ele : e.second) {
            string word = ele.first;
            double weight = calculateWeight(word, doc_id);
            weightMap[word] = weight;
            sumofWeightSquares += weight * weight;
        }
        // 第二次遍历进行权重归一化
        for (const auto& ele : e.second) {
            string word = ele.first;
            double normal_weight = weightMap[word] / sqrt(sumofWeightSquares);
            invertIndexTable_[word].push_back({doc_id, normal_weight});
        }
    }
}
// 原错误的处理过程
/* void PageLibPreprocessor::buildInvetIndexTable() { */
/*     cerr << "buildInvetIndexTable() start...\n"; */
/*     string new_ripepage_path = configMap_["newripepage_PATH"]; // 获取新网页库路径 */
/*     set<string> stoplist = Configuration::getInstance()->stopWorldList(); // 停用词列表 */
    
/*     ifstream new_page_lib(new_ripepage_path); */
/*     if (!new_page_lib) { */
/*         cerr << "processWebs: open file failed " << new_ripepage_path << "\n"; */
/*     } */

/*     string line; */
/*     int doc_id; */
/*     int doc_pos; */
/*     int doc_length; */
/*     WebPage webPage; */
/*     const size_t buffer_size = 1024 * 1024; // 1MB */
/*     std::vector<char> buff(buffer_size); */

/*     // 依次获取网页 */
/*     for (auto& e : offsetLib_) { //offset_lib -> unordered_map<int, pair<int,int>> doc_id = e.first; */
/*         cerr << "doc_id:" << doc_id << " processing ...\n"; */
/*         doc_id = e.first; */
/*         doc_pos = e.second.first; */
/*         doc_length = e.second.second; */

/*         double weight_squares = 0; // 记录每篇文章的单词权重平方和 */

/*         new_page_lib.seekg(doc_pos); // 移动文件指针 */
/*         new_page_lib.read(buff.data(), doc_length); // 读取文件到buff中 */

/*         string doc(buff.data(), doc_length); */
/*         webPage.setDoc(doc); */
/*         webPage.parseXml(); */
/*         string content = webPage.docContent(); //获取网页内容 */
/*         vector<string> tmp = wordCutter_->cut(content); // 将内容进行分词 */
/*         map<string, double> weightMap;// 用来记录当前内容中单词权重 */
/*         for (const auto& word : tmp) { */
/*             if (stoplist.count(word) == 0) { // 去停用词 */
/*                 double IDF = calculateIDF(word, doc_id); */
/*                 weightMap[word] = IDF; */
/*                 weight_squares += IDF * IDF; */
/*             } */
/*         } */
/*         for (const auto& e : weightMap) { */
/*                 double normalized_IDF = e.second / sqrt(weight_squares); */
/*                 invertIndexTable_[e.first].push_back({doc_id, normalized_IDF}); */
/*         } */
/*     } */
/*     new_page_lib.close(); */
/* } */

void PageLibPreprocessor::StoreOnDisk() {
    cerr << "StoreOnDisk() start...\n";
    string newoffset_lib = configMap_["newoffset_PATH"];
    string invertIndex_lib = configMap_["invertIndex_PATH"];

    ofstream ofs_offsetlib(newoffset_lib);
    if (!ofs_offsetlib) {
        cerr << "open ofs_offsetlib failed\n";
    }
    for (const auto& e : offsetLib_) {
        ofs_offsetlib << e.first << " "
                      << e.second.first << " "
                      << e.second.second << "\n";
    }

    ofstream ofs_invertIndexlib(invertIndex_lib);
    if (!ofs_invertIndexlib) {
        cerr << "open ofs_invertIndexlib failed\n";
    }
    for (const auto& e : invertIndexTable_) {
        ofs_invertIndexlib << e.first << " ";
        for (const auto& pair : e.second) {
            ofs_invertIndexlib << pair.first << " "
                               << pair.second << " ";
        }
        ofs_invertIndexlib << "\n";
    }
}

void PageLibPreprocessor::getSimhash(const string& content, size_t top_n, uint64_t& u64) {
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

double PageLibPreprocessor::calculateWeight(const string& word, int doc_id) {
    int DF = DF_map_[word].size(); // 某个单词在所有文章中出现的次数
    int TF = TF_map_[doc_id][word];
    double IDF = log2(doc_count_ / (DF + 1) + 1);
    double weight = TF * IDF;
    return weight;
}

// 处理文章并统计词频
void PageLibPreprocessor::processDocument(int docId, const string& content) {
    vector<string> tmp = wordCutter_->cut(content); // 将内容进行分词
    set<string> stoplist = Configuration::getInstance()->stopWorldList(); // 停用词列表

    WordCountPerDoc wordCount; // 存储当前文档中的词频

    // 遍历文档中的每个单词
    for (const auto& word : tmp) {
        // 去除停用词
        if (stoplist.count(word) != 0) continue;

        // 记录单词在该文档中的出现次数
        ++wordCount[word];

        // 记录该单词在哪些文档中出现
        DF_map_[word].insert(docId);
    }

    // 将当前文档的词频统计结果保存
    TF_map_[docId] = wordCount;
}
