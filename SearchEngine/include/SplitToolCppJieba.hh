#ifndef __SPLITTOOLCPPJIEBA_H__
#define __SPLITTOOLCPPJIEBA_H__

#include "SplitTool.hh"
#include "Configuration.hh"

class SplitToolCppJieba : public SplitTool{
public:
    SplitToolCppJieba();
    ~SplitToolCppJieba() override;

    vector<string> cut(const string& sentence) override;

private:
    Configuration* conf_;
};

#endif

