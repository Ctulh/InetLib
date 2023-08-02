//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include <memory>
#include "ISocket.hpp"
#include <cinttypes>


class Socket;
using SocketPtr = std::shared_ptr<Socket>;

enum class SOCK_TYPE {
    TCP = 1,
    UDP = 2
};

class Socket: public ISocket {
public:
    explicit Socket(int fd);

    explicit Socket(const InetAddress& inetAddress, SOCK_TYPE sockType): m_sockConnectionType(sockType)
    {
        m_inetAddress = std::make_shared<InetAddress>(inetAddress);
        m_socketFd = socket(AF_INET,
                            ((sockType == SOCK_TYPE::TCP) ? SOCK_STREAM : SOCK_DGRAM)| SOCK_CLOEXEC,
                          0);
    }
    virtual ~Socket();

public:
    int bind() const override;
    int listen() const override;
    int accept() const override;

    int fd() const override;

    int receive(char* msg, int len) const override;
    int receive(std::string& msg) const override;
    int send(const char* msg, int len) const override;

    bool connect(std::int32_t timeoutSec = -1, std::int32_t timeoutUSec = -1);
    bool isConnected() const;

    bool setNonBlocking() const;

    void shutDown() override;
private:
    int writeToSock(const char* msg, int len) const;
    int readFromSock(int fd, char* buf, int bufSize) const;
private:
    SOCK_TYPE m_sockConnectionType = SOCK_TYPE::TCP;
    bool m_isConnected;
    int m_socketFd;
    std::shared_ptr<InetAddress> m_inetAddress;
};