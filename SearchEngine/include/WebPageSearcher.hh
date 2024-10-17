#ifndef __WEBPAGESEARCHER_H__
#define __WEBPAGESEARCHER_H__

#include "TcpConnection.h"
#include "SplitToolCppJieba.hh"

#include <string>

using std::string;


class WebPageSearcher {
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
public:
    WebPageSearcher(string keys, const TcpConnectionPtr& conn, SplitTool* wordCutTool);
    void response();
private:
    string doQuery();

private:
    string sentence_; // 查询关键句
    TcpConnectionPtr conn_; // TcpConnection对象
    SplitTool* wordCutTool_;
};

#endif

