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
}

int SocketSSL::connect() {
    auto addr = m_inetAddress->getSockAddr();
    auto result = ::connect(m_socketFd, addr, sizeof(*addr));
    if(result != 0)
        std::cout << "Error socketSSL connect";
    m_ctx = initCtx();
}

int SocketSSL::bind() {
    return ::bind(m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), sizeof(sockaddr));
}

int SocketSSL::listen() {
    return ::listen(m_socketFd, SOMAXCONN);
}

int SocketSSL::accept() {
    socklen_t addrLength = sizeof(sockaddr_in);
    return ::accept ( m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), &addrLength);
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
    return SSL_write(m_ssl, msg, len);
}

void SocketSSL::shutDown() {
    close(m_socketFd);
}

SSL_CTX *SocketSSL::initCtx() {
    std::call_once(m_initializationFlag, [](){
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
    });

    SSL_METHOD const* method;
    SSL_CTX *ctx;
    method = TLS_client_method();  /* Create new client-method instance */
    ctx = SSL_CTX_new(method);   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}



std::once_flag SocketSSL::m_initializationFlag;
