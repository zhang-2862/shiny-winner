#include <iostream>
#include <string>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 将wordList放入set中
        copy(wordList.begin(), wordList.end(), std::inserter(set_, set_.begin()));
        // 若wordList中不存在endWord，则直接返回0
        if (set_.count(endWord) == 0) {
            return 0;
        }
        beginWord_ =  beginWord;
        endWord_ = endWord;
        vec_.push_back(beginWord); // 将首单词放入vector中
        vector<string> res = search_endWord(set_, vec_);
        return res.size();
    }

    vector<string> search_endWord(set<string> wordList, vector<string> resList) {
        auto it = wordList.begin();
        while (*it != endWord_ && !set_.empty()) {
            if (isAbleToconnect(resList.back(), *it)) {
                vec_.push_back(*it);
                wordList.erase(it);// 将加入链表的元素从set中移除
                resList = search_endWord(wordList, resList);
            } else {
                ++it; // 继续匹配
            }
        }
        return resList;
    }
    // 用来比较两个单词是否只相差1个字母
    bool isAbleToconnect(const string& lhs, const string& rhs) {
        // 获取单词的长度
        int length = lhs.size();
        int count = 0; // 不等字母个数
        for (size_t idx = 0; idx != length; ++idx) {
            if (lhs[idx] != rhs[idx]) {
                ++count;
            }
        }
        return count < 2; // 不同字母数为 0 或 1 返回true
    }

private:
    string beginWord_;
    string endWord_;
    int min_size;
    set<string> set_;// 存储字典
    vector<string> vec_; //结果集
};

int main(int argc, char* argv[]) {
    cout << "Hello,World" << endl;

    return 0;
}

