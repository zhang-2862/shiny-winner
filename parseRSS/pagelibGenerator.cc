#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

using namespace std;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader(size_t init_vsize); 
    void parseRss(const string& filename);//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
 };   

RssReader::RssReader(size_t init_vsize) 
{
    _rss.reserve(init_vsize);
}

void RssReader::parseRss(const string& filename) {
    XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if (doc.ErrorID()) {
        cerr << "LoadFile fail" << endl;
        return;
    }

    XMLElement* itemNode = 
        doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
    cout << "parse start" << endl;
    while (itemNode) {
        string title = itemNode->FirstChildElement("title")->GetText();
        string link = itemNode->FirstChildElement("link")->GetText();
        string description = itemNode->FirstChildElement("description")->GetText();
        string content = itemNode->FirstChildElement("content:encoded")->GetText();
    cout << "parse ..." << endl;

        regex reg("<[^>]+>");
        description = regex_replace(description, reg, "");
        content = regex_replace(content, reg, "");

        RssItem rssItem;

        rssItem.title = title;
        rssItem.link = link;
        rssItem.description = description;
        rssItem.content = content;

        _rss.push_back(rssItem);

        itemNode = itemNode->NextSiblingElement("item");
    }
    cout << "parse over" << endl;
}

void RssReader::dump(const string & filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "open " << filename << " is invalid" << endl;
        return;
    }

    size_t index = 1;
    for (auto& e : _rss) {
        ofs << "<doc>\n\t<docid>" << index++ 
            << "</docid>\n\t<title>" << e.title
            << "</title>\n\t<link>" << e.link
            << "</link>\n\t<description>" << e.description
            << "</description>\n\t<content>" << e.content
            << "</content>\n</doc>\n";
    }
    ofs.close();
    cout << "dump over" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "usage: filename" << endl;
    }
    RssReader rssR(1024);
    cout << "start" << endl;

    rssR.parseRss(argv[1]);
    rssR.dump("pagelib.dat");
    
    return 0;
}

