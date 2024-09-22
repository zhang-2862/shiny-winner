#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <string>
#include <cstring>
#include <arpa/inet.h>

using std::string;

class InetAddress {
public:
    InetAddress(const string& ip, unsigned short port); 
    InetAddress(const struct sockaddr_in& addr); 
    ~InetAddress(); 
    string getIp();
    unsigned short getPort();
    struct sockaddr_in* getInetAddressPtr();

private:
    struct sockaddr_in addr_;
};

#endif

