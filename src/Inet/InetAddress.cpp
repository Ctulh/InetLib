//
// Created by egor on 10/13/22.
//

#include "InetAddress.hpp"
#include <cstring>
#include <netdb.h>

InetAddress::InetAddress(uint16_t port) {
    memset(&m_addr, 0, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

InetAddress::InetAddress(std::string_view host, uint16_t port) {
    memset(&m_addr, 0, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    m_addr.sin_addr.s_addr = inet_addr(host.data());
    //m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton ( AF_INET, ip.data(), &m_addr.sin_addr );
}

InetAddress::InetAddress(const sockaddr_in &addr): m_addr(addr) {}

void InetAddress::setPort(uint16_t port) {
    m_addr.sin_port = htons(port);
}

const sockaddr *InetAddress::getSockAddr() const {
    return static_cast<const sockaddr*>((void*)(&m_addr));
}