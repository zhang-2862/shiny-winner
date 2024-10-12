#include "Configuration.hh"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using std::ifstream;
using std::istringstream;

Configuration* Configuration::config_instance_ = nullptr;
Configuration::AutoRelease Configuration::ar_;
static const string conf_path = "conf/myconf.conf"; // 配置文件路径
static const string words_zh_path_name = "stop_words_zh"; // 中文停用词的key
static const string words_eng_path_name = "stop_words_eng"; // 英文停用词的key

Configuration* Configuration::getInstance() {
    if (config_instance_ == nullptr) {
        config_instance_ = new Configuration(conf_path);
        config_instance_->getConfigMap();
        config_instance_->getStopWorldList();
    }
    return config_instance_;
}

Configuration::Configuration(const string& filepath)
    : filepath_(filepath)
{}

map<string, string>& Configuration::configMap() {
    return configMap_;
}

set<string>& Configuration::stopWorldList() {
    return stopWordList_;
}


void Configuration::getConfigMap() {

    ifstream ifs(filepath_);
        // 检查 ifstream 是否成功打开
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file: " << filepath_ << std::endl;
    }

    string line;
    string key;
    string value;
    while (getline(ifs, line)) {
        istringstream iss(line);
        iss >> key >> value;
        configMap_[key] = value;
    }

    ifs.close();
}

void Configuration::getStopWorldList() {
    string words_eng_path = configMap_[words_eng_path_name];
    string words_zh_path = configMap_[words_zh_path_name];
    /* std::cout << words_eng_path << " " << words_zh_path << endl; */
    ifstream ifs1(words_eng_path);
    ifstream ifs2(words_zh_path);
    // 检查 ifstream 是否成功打开
    if (!ifs1.is_open()) {
        std::cerr << "Failed to open file: " << words_eng_path << std::endl;
    }

    if (!ifs2.is_open()) {
        std::cerr << "Failed to open file: " << words_zh_path << std::endl;
    }

    string line;
    string key;
    while (getline(ifs1, line)) {
        istringstream iss(line);
        iss >> key;
        stopWordList_.insert(key);
    }

    while (getline(ifs2, line)) {
        istringstream iss(line);
        iss >> key;
        stopWordList_.insert(key);
    }

    ifs1.close();
    ifs2.close();
}

