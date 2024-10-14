#include "WebPage.hh"

#include "tinyxml2.h"

#include <iostream>

using std::cerr;

WebPage::WebPage(string& doc)
    : doc_(doc)
{
    parseXml(); //解析文本
}

WebPage::~WebPage() {

}

string WebPage::doc() { return doc_; };

int WebPage::docId() { return docId_; };

string WebPage::docTitle() { return docTitle_; }; 

string WebPage::docUrl() { return docUrl_; };

string WebPage::docContent() { return docContent_; };

void WebPage::parseXml() {
    // 创建XML文档对象
    tinyxml2::XMLDocument doc;
    
    // 从字符串加载XML
    tinyxml2::XMLError eResult = doc.Parse(doc_.c_str());
    if (eResult != tinyxml2::XML_SUCCESS) {
        cerr << "Error: Unable to parse XML string!\n";
        return;
    }

    // 查找第一个 <doc> 元素
    tinyxml2::XMLElement* docElement = doc.FirstChildElement("doc");
    if (!docElement) {
        cerr << "Error: No <doc> element found!\n"; 
        return;
    }

    // 解析 <docid>
    tinyxml2::XMLElement* docidElement = docElement->FirstChildElement("docid");
    string docid = docidElement ? docidElement->GetText() : "N/A";

    // 解析 <title>
    tinyxml2::XMLElement* titleElement = docElement->FirstChildElement("title");
    string title = titleElement ? titleElement->GetText() : "N/A";

    // 解析 <link>
    tinyxml2::XMLElement* linkElement = docElement->FirstChildElement("link");
    string link = linkElement ? linkElement->GetText() : "N/A";

    // 解析 <content>
    tinyxml2::XMLElement* contentElement = docElement->FirstChildElement("content");
    string content = contentElement ? contentElement->GetText() : "N/A";

    docId_ = std::stoi(docid);
    docTitle_ = title;
    docUrl_ = link;
    docContent_ = content;
}

