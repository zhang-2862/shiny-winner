#include "PageLib.hh"
#include "Configuration.hh"

#include "tinyxml2.h"

#include <regex>
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::cerr;

PageLib::PageLib(DirScanner& dirScanner)
    : dirScanner_(dirScanner)
{

}

PageLib::~PageLib() {

}

void PageLib::create() {
    auto map = Configuration::getInstance()->configMap();
    string pagelib_path = map["pagelib_PATH"];

    /* cerr << "pagelib_path: " << pagelib_path << "\n"; */

    dirScanner_(pagelib_path); // 创建目录扫描器

    // 打开rapepage文件，用来存储处理好的xml文档
    string ripepage_path = map["ripepage_PATH"];
    ofstream ofs(ripepage_path);
    if (!ofs) {
        cerr << "open rapepage failed.\n";
        return;
    }

    int idx = 1; // 用于记录文档编号
    int pos = 0; // 记录每个xml项的起始位置 
    int length = 0; // 记录xml项长度

    // 处理xml文件
    for (auto& file : dirScanner_.files()) {
        tinyxml2::XMLDocument doc;
        doc.LoadFile(file.c_str());
        if (doc.ErrorID()) {
            cerr << "load file failed: " << doc.ErrorStr() << endl;
            return;
        }

        // 解析xml文件的各个节点，添加空指针检查
        tinyxml2::XMLElement* rssElement = doc.FirstChildElement("rss");
        if (!rssElement) {
            cerr << "No <rss> element found in file: " << file << endl;
            continue;
        }

        tinyxml2::XMLElement* channelElement = rssElement->FirstChildElement("channel");
        if (!channelElement) {
            cerr << "No <channel> element found in file: " << file << endl;
            continue;
        }

        tinyxml2::XMLElement* itemNode = channelElement->FirstChildElement("item");
        if (!itemNode) {
            cerr << "No <item> element found in file: " << file << endl;
            continue;
        }

        while (itemNode) {
            // 使用 std::string 来存储文本内容
            string title = itemNode->FirstChildElement("title") ? itemNode->FirstChildElement("title")->GetText() : "N/A";
            string link = itemNode->FirstChildElement("link") ? itemNode->FirstChildElement("link")->GetText() : "N/A";
            string content = itemNode->FirstChildElement("description") ? itemNode->FirstChildElement("description")->GetText() : "N/A";

            std::regex reg("<[^>]+>"); // 定义去除多余元素的规则
            content = regex_replace(content, reg, "");

            // 存入rapepage中
            pos = ofs.tellp();
            ofs << "<doc>\n\t<docid>" << idx 
                << "</docid>\n\t<title>" << title 
                << "</title>\n\t<link>" << link 
                << "</link>\n\t<content>" << content
                << "</content>\n</doc>";
            ofs << '\n';
            length = static_cast<int>(ofs.tellp()) - pos;
            offsetLib_[idx++] = {pos, length};

            itemNode = itemNode->NextSiblingElement("item");
        }
    }

    ofs.close();
}

// 将offsetLib_存入磁盘
void PageLib::store() {
    auto map = Configuration::getInstance()->configMap();
    string pageoffset_path = map["pageoffset_PATH"];
    // 打开网页偏移库文件
    ofstream ofs(pageoffset_path);
    if (!ofs) {
        cerr << "open rapepage failed.\n";
        return;
    }
    for (auto& e : offsetLib_) {
        ofs << e.first <<" "
            << e.second.first << " "
            << e.second.second << "\n";
    }
    ofs.close();
}

