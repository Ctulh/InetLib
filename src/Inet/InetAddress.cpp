//
// Created by egor on 10/13/22.
//

#include "InetAddress.hpp"
#include <cstring>

InetAddress::InetAddress(std::string_view ip, uint16_t port) {
    memset(&m_addr, 0, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_addr.sin_port = htons(port);
    //m_addr.sin_addr.s_addr = inet_addr(ip.data());
}

InetAddress::InetAddress(const sockaddr_in &addr): m_addr(addr) {}

void InetAddress::setPort(uint16_t port) {
    m_addr.sin_port = htons(port);
}

const sockaddr *InetAddress::getSockAddr() const {
    return static_cast<const sockaddr*>((void*)(&m_addr));
}