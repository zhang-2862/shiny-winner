#ifndef __DirScanner_H__
#define __DirScanner_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

class DirScanner {
public:
    DirScanner();
    ~DirScanner();

    void operator()(const string& dir);  //重载函数调用运算符，调用traverse函数


    vector<string>& files(); 

private:
    void traverse(const string& dirname);

private:
    vector<string> files_;
};

#endif

