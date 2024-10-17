#include "WebPageSearcher.hh"
#include "WebPageQuery.hh"
#include "Tlv.hh"

WebPageSearcher::WebPageSearcher(string keys,
                                 const TcpConnectionPtr& conn,
                                 SplitTool* wordCutTool) 
    : sentence_(keys),
      conn_(conn),
      wordCutTool_(wordCutTool)
{

}

string WebPageSearcher::doQuery() {
    WebPageQuery query(wordCutTool_);
    string result = query.doQuery(sentence_);
    return result;
}

void WebPageSearcher::response() {
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
