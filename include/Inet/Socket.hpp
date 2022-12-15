//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include <memory>
#include "ISocket.hpp"

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
    int bind() override;
    int listen() override;
    int accept() override;

    int fd() const override;

    int recv(char* msg, int len) const override;
    int recv(std::string& msg) const override;
    int send(const char* msg, int len) const override;
    std::shared_ptr<InetAddress> getInetAddr() const {
        return m_inetAddress;
    }


    int connect();
    bool isConnected() const;

    bool setNonBlocking() const;

    void shutDown() override;
private:
    int read(int fd, char* buf, int bufSize) const;
private:
    SOCK_TYPE m_sockConnectionType = SOCK_TYPE::TCP;
    bool m_isConnected;
    int m_socketFd;
    std::shared_ptr<InetAddress> m_inetAddress;
};