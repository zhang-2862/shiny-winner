#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <vector>
#include <string>
#include <set>
#include <map>

using std::vector;
using std::pair;
using std::string;
using std::set;
using std::map;

class Dictionary {
    class AutoRelease { // 实现自动释放单例
    public:
        AutoRelease() {

        }
        ~AutoRelease() {
            if (dic_instance_) {
                delete dic_instance_;
                dic_instance_ = nullptr;
            }
        }
    };
public:
    static Dictionary* getInstance();
    vector<pair<string, int>> doQuery(const string& str);

private:
    Dictionary() = default;
    ~Dictionary() = default;
    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) =delete;
    void queryIndex();
    int distance(string candidate);
    void init(string dict_path, string index_path);
    vector<string> getWord(const string& str); // 获取分字
    size_t nBytesCode(const char ch); // 获取整个字的字符长度

private:
    vector<pair<string,int>> dict_;
    map<string, set<int>> index_;
    static Dictionary* dic_instance_;
    static AutoRelease ar_;
};

#endif

