#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
#include <map>
#include <set>

#include <iostream>

using std::string;
using std::map;
using std::set;
using std::cout;
using std::endl;

class Configuration {
    class AutoRelease { // 实现自动释放单例
    public:
        AutoRelease() {

        }
        ~AutoRelease() {
            if (config_instance_) {
                delete config_instance_;
                config_instance_ = nullptr;
            }
        }
    };
public:
    static Configuration* getInstance();

    map<string, string>& configMap();
    set<string>& stopWorldList();


private:
    void getConfigMap();
    void getStopWorldList();

public:
    // 仅供测试使用
    void printMap() {
        for (auto& pair : configMap_) {
            cout << "key: " << pair.first << " value: " << pair.second
                 << endl;
        }
    }

    void printSet() {
        for (auto& e : stopWordList_) {
            cout << "key: " << e << endl;
        }
    }

private:
    Configuration(const string& filepath);
    Configuration() = default;
    ~Configuration() = default;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

private:
    string filepath_; // 配置文件路径
    map<string, string> configMap_; // 配置文件内容
    set<string> stopWordList_; // 停用词词集
    static Configuration* config_instance_;
    static AutoRelease ar_;
};

#endif

