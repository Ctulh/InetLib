//
// Created by egor on 10/13/22.
//

#include "InetAddress.hpp"
#include <cstring>
#include <netdb.h>
#include <ctype.h>
#include <iostream>
#include <string>

InetAddress::InetAddress(uint16_t port) {
    memset(&m_addr, 0, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

InetAddress::InetAddress(std::string_view url) {
    if(not url.empty()) {
        std::string hostname;
        std::string urlString (url.data());
        std::string portString = "443";

        struct hostent *hostStruct;
        int port;

        if(urlString.back() == '/')
            urlString.back() = '\0';

        hostname = urlString.substr(urlString.find("://") + 3, urlString.size());

        if(hostname.find(':') != std::string::npos) {
            auto pos = hostname.find(':');
            portString = hostname.substr(pos+1, hostname.size());
            hostname[pos] = '\0';
        }


        if ( (hostStruct = gethostbyname(hostname.c_str())) == NULL ) {
            std::cout << "Error: Cannot resolve hostname: " << hostname << '\n';
            abort();
        }

        port = atoi(portString.c_str());

        m_addr.sin_family=AF_INET;
        m_addr.sin_port=htons(port);
        m_addr.sin_addr.s_addr = *(long*)(hostStruct->h_addr);
    }
}

InetAddress::InetAddress(std::string_view host, uint16_t port) {
    if(not host.empty()) {
        if (isdigit(host[0])) {
            memset(&m_addr, 0, sizeof(m_addr));
            m_addr.sin_family = AF_INET;
            m_addr.sin_port = htons(port);
            m_addr.sin_addr.s_addr = inet_addr(host.data());
        }
        else {
            std::string hostname;
            struct hostent *hostStruct;
            std::string urlString (host.data());

            if(urlString.back() == '/')
                urlString.back() = '\0';

            hostname = urlString.substr(urlString.find("://") + 3, urlString.size());

            if ( (hostStruct = gethostbyname(hostname.c_str())) == NULL ) {
                std::cout << "Error: Cannot resolve hostname: " << hostname << '\n';
                abort();
            }

            m_addr.sin_family=AF_INET;
            m_addr.sin_port=htons(port);
            m_addr.sin_addr.s_addr = *(long*)(hostStruct->h_addr);
        }
    }
}

InetAddress::InetAddress(const sockaddr_in &addr): m_addr(addr) {}

void InetAddress::setPort(uint16_t port) {
    m_addr.sin_port = htons(port);
}

const sockaddr *InetAddress::getSockAddr() const {
    return static_cast<const sockaddr*>((void*)(&m_addr));
}