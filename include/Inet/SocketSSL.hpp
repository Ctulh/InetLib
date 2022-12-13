//
// Created by ctuh on 12/13/22.
//

#pragma once

#include "ISocket.hpp"
#include "InetAddress.hpp"

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <mutex>
#include <iostream>
#include <memory>

class SocketSSL: public ISocket {
public:
    explicit SocketSSL(int fd);

    explicit SocketSSL(const InetAddress& inetAddress)
    {
        m_inetAddress = std::make_unique<InetAddress>(inetAddress);
        m_socketFd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);
    }
    ~SocketSSL();

public:
    int connect();
    int bind() override;
    int listen() override;
    int accept() override;

    int fd() const override;

    int recv(char* msg, int len) const override;
    int recv(std::string& msg) const override;
    int send(const char* msg, int len) const override;

    void shutDown() override;
private:
    SSL_CTX* initCtx();

private:
    std::unique_ptr<InetAddress> m_inetAddress;
    static std::once_flag m_initializationFlag;
    int m_socketFd;
    SSL_CTX* m_ctx;
    SSL* m_ssl;
};