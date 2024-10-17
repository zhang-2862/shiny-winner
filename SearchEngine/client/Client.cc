#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Tlv.hpp"  // 引入你定义的 TLV 头文件

// 定义最大缓冲区长度
#define BUFFER_SIZE 1024

// 发送 TLV 数据包的函数
void sendTLV(int sockfd, const Message& msg) {
    // 序列化消息为字节数组
    std::vector<char> buffer = Serialize(msg);
    
    // 发送数据
    ssize_t bytesSent = send(sockfd, buffer.data(), buffer.size(), 0);
    if (bytesSent < 0) {
        std::cerr << "Failed to send data." << std::endl;
    }
}

// 接收并打印服务器的响应
void receiveResponse(int sockfd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesReceived = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';  // 确保字符串以 null 结束
        Message msg = Deserialize(std::vector<char>(buffer, buffer + bytesReceived));  // 反序列化响应
        std::cout << "Server response (type " << static_cast<int>(msg.type) << "): " << msg.data << std::endl;
    } else {
        std::cout << "No response from server or connection closed." << std::endl;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    // 设置服务器地址信息
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);  // 服务器端口
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 服务器 IP 地址

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("test");
        std::cerr << "Connection failed." << std::endl;
        close(sockfd);
        return -1;
    }

    std::cout << "Connected to server." << std::endl;

    // 命令行交互：选择查询类型并输入查询内容
    while (true) {
        std::cout << "\nChoose query type:\n1. Keyword Query\n2. Sentence Query\nEnter choice (1 or 2): ";
        int choice;
        std::cin >> choice;

        if (choice != 1 && choice != 2) {
            std::cout << "Invalid choice. Exiting." << std::endl;
            break;
        }

        std::cin.ignore();  // 清除输入缓冲区
        std::cout << "Enter the query: ";
        std::string query;
        std::getline(std::cin, query);
        query += '\n';

        // 创建消息对象
        Message msg;
        msg.type = (choice == 1) ? kKeyword : kKeySentence; // 设置消息类型
        msg.data = query;  // 设置数据内容
        msg.length = query.size();  // 设置数据长度

        // 发送 TLV 数据包到服务器
        sendTLV(sockfd, msg);

        // 接收服务器的响应
        receiveResponse(sockfd);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}

