//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include <memory>

enum SOCK_TYPE {
    TCP = 1,
    UDP = 2
};

class Socket {
public:
    explicit Socket(int fd);

    explicit Socket(const InetAddress& inetAddress, SOCK_TYPE sockType)
    {
        m_inetAddress = std::make_unique<InetAddress>(inetAddress);
        m_socketFd = socket(AF_INET,
                            ((sockType == TCP) ? SOCK_STREAM : SOCK_DGRAM)| SOCK_CLOEXEC,
                          0);
    }
    virtual ~Socket();

public:
    bool bind();
    int listen();
    int accept();

    int fd() const;

    bool connect();
    bool isConnected() const;

    bool setNonBlocking() const;

    void shutDown();
private:
    bool m_isConnected;
    int m_socketFd;
    std::unique_ptr<InetAddress> m_inetAddress;
};