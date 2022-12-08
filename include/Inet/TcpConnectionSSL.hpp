//
// Created by ctuh on 12/8/22.
//

#pragma once

#include "TcpConnection.hpp"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class TcpConnectionSSL: public TcpConnection {
public:
    TcpConnectionSSL(InetAddress const& inetAddress): TcpConnection(inetAddress) {
        InitializeSSL();
        sslctx = SSL_CTX_new( SSLv23_server_method());
        SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
        cSSL = SSL_new(sslctx);
        SSL_set_fd(cSSL, m_socket->fd());
    }
    TcpConnectionSSL(int fd): TcpConnection(fd) {
        InitializeSSL();
        sslctx = SSL_CTX_new( SSLv23_server_method());
        SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
        cSSL = SSL_new(sslctx);
        SSL_set_fd(cSSL, m_socket->fd());
    }
    TcpConnectionSSL(std::shared_ptr<Socket> socket): TcpConnection(socket) {
        InitializeSSL();
        sslctx = SSL_CTX_new( SSLv23_server_method());
        SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
        cSSL = SSL_new(sslctx);
        SSL_set_fd(cSSL, m_socket->fd());
    }
public:

    void send(const char *msg, std::size_t len) override {
        SSL_write(cSSL, msg, len);
    }

    void recv(std::string &msg) override {
        char charBuffer[1024];
        SSL_read(cSSL, &charBuffer, 1024);
        msg.clear();
        msg = charBuffer;
    }

private:
    void InitializeSSL()
    {
        SSL_load_error_strings();
        SSL_library_init();
        OpenSSL_add_all_algorithms();
    }


protected:
    SSL_CTX *sslctx;
    SSL *cSSL;
};