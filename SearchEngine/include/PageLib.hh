#ifndef __PAGELIB_H__
#define __PAGELIB_H__

#include "DirScanner.hh"
#include "Configuration.hh"

#include <utility>
#include <map>

using std::map;
using std::pair;

class PageLib {
public:
    PageLib(DirScanner& dirScanner);
    ~PageLib();

    void create();
    void store();
private:
    bool isAllWhitespace(const string& str);

private:
    DirScanner& dirScanner_;
    /* vector<string> files_; */
    map<int, pair<int, int>> offsetLib_;
};

#endif

