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
    explicit SocketSSL(const InetAddress& inetAddress);
    ~SocketSSL();

public:
    bool connect() const;
    bool bind() const override;
    bool listen() const override;
    bool accept() const override;

    int nativeHandle() const override;

    //int receive(char* msg, int len) const override;
    //int receive(std::string& msg) const override;
    //int send(const char* msg, int len) const override;

    bool shutDown(int how) override;
private:
    static SSL_CTX* initCtx();

private:
    std::unique_ptr<InetAddress> m_inetAddress;
    static std::once_flag m_initializationFlag;
    int m_socketFd;
    SSL_CTX* m_ctx;
    SSL* m_ssl;
};