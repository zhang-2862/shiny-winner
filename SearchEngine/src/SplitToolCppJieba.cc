#include "SplitToolCppJieba.hh"

#include "cppjieba/Jieba.hpp"

SplitToolCppJieba::SplitToolCppJieba()
    : conf_(Configuration::getInstance())
{

}

SplitToolCppJieba::~SplitToolCppJieba() {

}

vector<string> SplitToolCppJieba::cut(const string& sentence) {
    auto map = conf_->configMap();

    const char* const DICT_PATH = map["_conf.mapKey.DICT_PATH"].c_str();
    const char* const HMM_PATH = map["_conf.mapKey.HMM_PATH"].c_str();
    const char* const USER_DICT_PATH = map["_conf.mapKey.USER_DICT_PATH"].c_str();
    const char* const IDF_PATH  = map["_conf.mapKey.IDF_PATH"].c_str();
    const char* const STOP_WORD_PATH  = map["_conf.mapKey.STOP_WORD_PATH"].c_str();

    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);
    vector<string> words;
    
    jieba.Cut(sentence, words, true);

    return words;
}
