//
// Created by ctuh on 12/13/22.
//

#include "SocketSSL.hpp"

namespace {
    constexpr int BUFFER_SIZE = 1024;
}

SocketSSL::~SocketSSL() {
    SSL_CTX_free(m_ctx);
    SSL_free(m_ssl);
    SSL_shutdown(m_ssl);
}

int SocketSSL::connect() {
    auto addr = m_inetAddress->getSockAddr();
    auto result = ::connect(m_socketFd, addr, sizeof(*addr));
    if(result != 0)
        std::cout << "Error socketSSL connect";
    if ( SSL_connect(m_ssl) == -1 )   /* perform the connection */
        ERR_print_errors_fp(stderr);
    return result;
}

int SocketSSL::bind() {
    return ::bind(m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), sizeof(sockaddr));
}

int SocketSSL::listen() {
    return ::listen(m_socketFd, SOMAXCONN);
}

int SocketSSL::accept() {
    socklen_t addrLength = sizeof(sockaddr_in);
    return ::SSL_accept(m_ssl);
}

int SocketSSL::fd() const {
    return m_socketFd;
}

int SocketSSL::recv(std::string &msg) const {
    int result;
    for(;;) {
        char buf[BUFFER_SIZE];
        result = SSL_read(m_ssl, buf, BUFFER_SIZE);
        if(result == BUFFER_SIZE) {
            msg += buf;
            continue;
        }
        else if(result == 0)
            return result;
        else if(result == -1) {
            return result;
        }
        else if(result < BUFFER_SIZE) {
            msg += buf;
            break;
        }
    }
    return result;
}

int SocketSSL::recv(char *msg, int len) const {
    return SSL_read(m_ssl, msg, len);
}

int SocketSSL::send(const char *msg, int len) const {
    auto result = SSL_write(m_ssl, msg, len);
    return result;
}

void SocketSSL::shutDown() {
    close(m_socketFd);
}

SSL_CTX *SocketSSL::initCtx() {
    std::call_once(m_initializationFlag, [](){
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
    });

    SSL_CTX *ctx;
    ctx = SSL_CTX_new(SSLv23_client_method());   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }

    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    return ctx;
}



std::once_flag SocketSSL::m_initializationFlag;
