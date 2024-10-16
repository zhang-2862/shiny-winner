#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include <string>
using std::string;

class WebPage {
public:
    WebPage();
    ~WebPage();

    void setDoc(const string& doc);
    string doc();
    int docId();
    string docTitle(); 
    string docUrl();
    string docContent();

    void parseXml(); //解析doc


private:
    string doc_; // 整篇文档包括xml
    int docId_; // 文档id
    string docTitle_; // 文档标题
    string docUrl_; // 文档URL
    string docContent_; // 文档内容
};

#endif

