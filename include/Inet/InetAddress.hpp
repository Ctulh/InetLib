//
// Created by egor on 10/13/22.
//

#pragma once

#include <string_view>
#include <cinttypes>
#include <string>

#ifdef _WIN32
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

class InetAddress {
public:
    InetAddress(std::string_view host, uint16_t port);
    InetAddress(std::string_view url);
    InetAddress(uint16_t port);
    InetAddress(const sockaddr_in& addr);

public:
    void setPort(uint16_t);
    const sockaddr* getSockAddr() const;

    std::string getHost() const;
    uint16_t getPort() const;
private:
    sockaddr_in m_addr;
    std::string m_host;
    uint16_t m_port;
};