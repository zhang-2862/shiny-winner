#include "InetAddress.hh"

InetAddress::InetAddress(const string& ip, unsigned short port) {
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    addr_.sin_port = htons(port);
} 

InetAddress::InetAddress(const struct sockaddr_in& addr)
    : addr_(addr)
{

} 

InetAddress::~InetAddress() {

} 

string InetAddress::getIp() {
    return inet_ntoa(addr_.sin_addr);
}

unsigned short InetAddress::getPort() {
    return ntohs(addr_.sin_port);
}

struct sockaddr_in* InetAddress::getInetAddressPtr() {
    return &addr_;
}
