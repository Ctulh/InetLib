//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include <memory>
#include "ISocket.hpp"

class Socket;
using SocketPtr = std::shared_ptr<Socket>;

enum SOCK_TYPE {
    TCP = 1,
    UDP = 2
};

class Socket: public ISocket {
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
    int bind() override;
    int listen() override;
    int accept() override;

    int fd() const override;

    int recv(char* msg, int len) const override;
    int recv(std::string& msg) const override;
    int send(const char* msg, int len) const override;

    bool connect();
    bool isConnected() const;

    bool setNonBlocking() const;

    void shutDown() override;
private:
    bool m_isConnected;
    int m_socketFd;
    std::unique_ptr<InetAddress> m_inetAddress;
};