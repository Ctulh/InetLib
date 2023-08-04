//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include <memory>
#include "ISocket.hpp"
#include <cinttypes>
#include "SocketType.hpp"

class Socket;
using SocketPtr = std::shared_ptr<Socket>;

class Socket: public ISocket {
public:
    explicit Socket(int fd);

    explicit Socket(const InetAddress& inetAddress, SocketType sockType): m_sockConnectionType(sockType)
    {
        m_inetAddress = std::make_shared<InetAddress>(inetAddress);
        m_socketFd = socket(AF_INET,
                            ((sockType == SocketType::TCP) ? SOCK_STREAM : SOCK_DGRAM)| SOCK_CLOEXEC,
                          0);
    }
    ~Socket() override;

public:
    bool bind() const override;
    bool listen() const override;
    bool accept() const override;
  //  bool connect() override;

    int nativeHandle() const override;

   // int receive(char* msg, int len) const override;
  //  int receive(std::string& msg) const override;
   // int send(const char* msg, int len) const override;

    bool isNonBlocking() const override;
    bool setNonBlocking() override;

    int getFlags() const override;
    bool setFlag(int flag, bool shouldEnable) override;
    bool setFlags(int flags) override;

    bool setConnectTimeout(std::chrono::milliseconds connectTimeout) override;
    bool setSendTimeout(std::chrono::milliseconds sendTimeout) override;
    bool setReceiveTimeout(std::chrono::milliseconds receiveTimeout) override;

    int getLastError() const override;
    InetAddress getInetAddress() const override;
    bool shutDown(int how) override;

protected:
    void setError() const;

private:
    mutable int m_lastError = 0;
    SocketType m_sockConnectionType = SocketType::TCP;
    bool m_isConnected;
    int m_socketFd;
    std::shared_ptr<InetAddress> m_inetAddress;
};