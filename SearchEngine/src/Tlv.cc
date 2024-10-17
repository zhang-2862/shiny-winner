#include "Tlv.hh"

#include <arpa/inet.h>

#include <string>
#include <vector>
#include <cstring> // For htonl and ntohl
#include <stdexcept>  // For std::invalid_argument
                      //
using std::string;


// 将消息序列化为字符串
std::vector<char> Serialize(const Message& msg) {
    // 计算总长度
    size_t total_length = sizeof(uint32_t) * 2 + msg.data.size();
    std::vector<char> buffer(total_length);

    // 写入类型
    uint32_t type = static_cast<uint32_t>(msg.type);
    std::memcpy(buffer.data(), &type, sizeof(type));

    // 写入长度
    uint32_t length = htonl(static_cast<uint32_t>(msg.data.size())); // 网络字节序
    std::memcpy(buffer.data() + sizeof(uint32_t), &length, sizeof(length));

    // 写入数据
    std::memcpy(buffer.data() + sizeof(uint32_t) * 2, msg.data.c_str(), msg.data.size());

    return buffer;
}

// 从字符串反序列化消息
Message Deserialize(const std::vector<char>& buffer) {
    if (buffer.size() < sizeof(uint32_t) * 2) { // 至少要有类型和长度
        throw std::invalid_argument("Invalid message format");
    }

    Message msg;

    // 读取类型
    const uint32_t* ptype = reinterpret_cast<const uint32_t*>(buffer.data());
    msg.type = static_cast<MessageType>(*ptype);

    // 读取长度
    const uint32_t* plength = reinterpret_cast<const uint32_t*>(buffer.data() + sizeof(uint32_t));
    uint32_t net_length = *plength;
    uint32_t host_length = ntohl(net_length); // 转换回主机字节序

    // 检查数据是否足够
    if (buffer.size() < (sizeof(uint32_t) * 2 + host_length)) {
        throw std::invalid_argument("Data size mismatch with length field");
    }

    // 读取数据
    msg.length = host_length;
    msg.data = std::string(buffer.data() + sizeof(uint32_t) * 2, host_length);

    return msg;
}


