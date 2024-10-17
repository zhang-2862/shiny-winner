#include "KeyRecommender.hh"
#include "Dictionary.hh"
#include "Tlv.hh"

#include "nlohmann/json.hpp"

static const int kNumberOfCandidateWords = 6; //候选词数量

KeyRecommender::KeyRecommender(string& sought,
                             const TcpConnectionPtr& conn)
    : sought_(sought),
      conn_(conn)
{

}
      
string KeyRecommender::doQuery() {
    // 先调用dictionnary的查询获取相关词，
    vector<pair<string, int>> 
        related_words{Dictionary::getInstance()->doQuery(sought_)};
    // 然后将相关词放入优先队列中排序确定候选词
    for (auto& e : related_words) {
        int dict = editDistance(sought_, e.first); // 获取最小编辑距离
        // 用单词，词频，最小编辑距离构建候选词对象
        CandidateResult candidate(e.first, e.second, dict);
        if (prique_.size() < kNumberOfCandidateWords) { //如果小于待返回候选词数量
            prique_.push(candidate);
        } else { // 否则弹出一个队头元素，再进行插入操作
            prique_.pop();
            prique_.push(candidate);
        }
    }
    // 将候选词从优先队列中弹出，并进行序列化
    int idx = 0;
    nlohmann::json jsonObject;
    while (!prique_.empty()) {
        jsonObject[idx] = prique_.top().word;
        prique_.pop();
    }
    return jsonObject.dump();
}

void KeyRecommender::response() {
    string result = doQuery();
    Message msg;
    msg.type = kReconmmendedWord;
    msg.length = result.length();
    msg.data = result;
    // tlv序列化
    vector<char> byteStream = Serialize(msg);
    string msgToSend(byteStream.begin(), byteStream.end());
    conn_->sendInLoop(msgToSend);
}

size_t KeyRecommender::nBytesCode(const char ch) {
    if(ch & (1 << 7))
    {
        int nBytes = 1;
        for(int idx = 0; idx != 6; ++idx)
        {
            if(ch & (1 << (6 - idx)))
            {
                ++nBytes;
            }
            else
                break;
        }
        return nBytes;
    }
    return 1;
 }

std::size_t KeyRecommender::length(const std::string &str) {
   std::size_t ilen = 0;
   for(std::size_t idx = 0; idx != str.size(); ++idx)
   {
       int nBytes = nBytesCode(str[idx]);
       idx += (nBytes - 1);
       ++ilen;
   }

  return ilen;
}

int KeyRecommender::triple_min(const int &a, const int &b, const int &c) {
   return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int KeyRecommender::editDistance(const std::string & lhs, const std::string &rhs) {
   //计算最小编辑距离-包括处理中英文
   size_t lhs_len = length(lhs);
   size_t rhs_len = length(rhs);
   int editDist[lhs_len + 1][rhs_len + 1];
   for(size_t idx = 0; idx <= lhs_len; ++idx)
   {
       editDist[idx][0] = idx;
   }
   for(size_t idx = 0; idx <= rhs_len; ++idx)
   {
       editDist[0][idx] = idx;
   }
   
   std::string sublhs, subrhs;
   for(std::size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len; ++dist_i, 
       ++lhs_idx)
   {
       size_t nBytes = nBytesCode(lhs[lhs_idx]);
       sublhs = lhs.substr(lhs_idx, nBytes);
       lhs_idx += (nBytes - 1);
       for(std::size_t dist_j = 1, rhs_idx = 0; 
           dist_j <= rhs_len; ++dist_j, ++rhs_idx)
       {
           nBytes = nBytesCode(rhs[rhs_idx]);
           subrhs = rhs.substr(rhs_idx, nBytes);
           rhs_idx += (nBytes - 1);
           if(sublhs == subrhs)
           {
               editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
           }
           else
           {
               editDist[dist_i][dist_j] = 
                   triple_min(editDist[dist_i][dist_j - 1] + 1,
                   editDist[dist_i - 1][dist_j] + 1,
                   editDist[dist_i - 1][dist_j - 1] + 1);
           }
       }
   }
   return editDist[lhs_len][rhs_len];
}

