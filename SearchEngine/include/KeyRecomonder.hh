#ifndef __KEYRECOMONDER_H__
#define __KEYRECOMONDER_H__

#include "TcpConnection.h"

#include <string>
#include <queue>

using std::string;
using std::priority_queue;

struct CandidateResult {
    string word;
    int freq;
    int dist;
    CandidateResult(const string& wrd, int frq, int dit)
        : word(wrd),
          freq(frq),
          dist(dit)
    {}
    bool operator<(const CandidateResult& other) const {
        if (dist != other.dist) {
            return dist > other.dist;  // 小的在前面，形成最小堆
        } else {
            return freq > other.freq;
        }
    }
};


class KeyRecomonder {
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
public:
    KeyRecomonder(string& sought, const TcpConnectionPtr& conn);
    string doQuery();// 把要返回给客户端的值进行序列化
private:
    size_t nBytesCode(const char ch);  //1. 求取一个字符占据的字节数
    size_t length(const std::string &str); //2. 求取一个字符串的字符长度
    int triple_min(const int &a, const int &b, const int &c);
    //3. 中英文通用的最小编辑距离算法
    int editDistance(const std::string & lhs, const std::string &rhs);

private:
    string sought_;
    TcpConnectionPtr conn_;
    priority_queue<CandidateResult> prique_;
};

#endif

