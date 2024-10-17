#ifndef __TLV_H__
#define __TLV_H__

#include <arpa/inet.h>

#include <string>
#include <vector>
#include <cstring> // For htonl and ntohl
#include <stdexcept>  // For std::invalid_argument
                      //
using std::string;

// 消息类型
enum MessageType {
    kKeyword = 1, //客户端发送关键字
    kKeySentence = 2, //客户端发送关键句
    kReconmmendedWord = 100, // 服务端推荐词
    kReconmmendedWeb = 200, // 服务端推荐网页
};

// 定义消息
struct Message {
    MessageType type;
    uint32_t length;
    string data; 
};


// 将消息序列化为字符串
std::vector<char> Serialize(const Message& msg);

// 从字符串反序列化消息
Message Deserialize(const std::vector<char>& buffer);

#endif

