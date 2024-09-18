#include "InetAddress.hh"

InetAddress::InetAddress(const string& ip, unsigned short port) {
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    addr_.sin_port = htons(port);
} 

inline InetAddress::InetAddress(const struct sockaddr_in& addr)
    : addr_(addr)
{

} 

inline InetAddress::~InetAddress() {

} 

inline string InetAddress::getIp() {
    return inet_ntoa(addr_.sin_addr);
}

inline unsigned short InetAddress::getPort() {
    return ntohs(addr_.sin_port);
}

inline struct sockaddr_in* InetAddress::getInetAddressPtr() {
    return &addr_;
}
