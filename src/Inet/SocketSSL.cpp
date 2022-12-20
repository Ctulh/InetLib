//
// Created by ctuh on 12/13/22.
//

#include "SocketSSL.hpp"

namespace {
    constexpr int BUFFER_SIZE = 1024;
}

SocketSSL::SocketSSL(const InetAddress &inetAddress) {
    m_inetAddress = std::make_unique<InetAddress>(inetAddress);
    m_socketFd = socket(AF_INET, SOCK_STREAM, 0);
    m_ctx = initCtx();

    m_ssl = SSL_new(m_ctx);
}

SocketSSL::~SocketSSL() {
    SSL_free(m_ssl);
    SSL_CTX_free(m_ctx);
}

int SocketSSL::connect() const {
    auto addr = m_inetAddress->getSockAddr();
    auto result = ::connect(m_socketFd, addr, sizeof(*addr));
    if(result != 0) {
        std::cout << "Error socketSSL connect";
        return -1;
    }

    SSL_set_fd(m_ssl, m_socketFd);

    if ( SSL_connect(m_ssl) == -1 )
        ERR_print_errors_fp(stderr);
    return result;
}

int SocketSSL::bind() const {
    return ::bind(m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), sizeof(sockaddr));
}

int SocketSSL::listen() const {
    return ::listen(m_socketFd, SOMAXCONN);
}

int SocketSSL::accept() const {
    socklen_t addrLength = sizeof(sockaddr_in);
    return ::SSL_accept(m_ssl);
}

int SocketSSL::fd() const {
    return m_socketFd;
}

int SocketSSL::recv(std::string &msg) const {
    int total;
    int result;

    for(;;) {
        char buf[BUFFER_SIZE];
        result = SSL_read(m_ssl, buf, BUFFER_SIZE);
        if(result == BUFFER_SIZE) {
            total += result;
            msg += buf;
            continue;
        }
        else if(result == 0)
            return total;
        else if(result == -1) {
            return total;
        }
        else if(result < BUFFER_SIZE) {
            total += result;
            msg += buf;
            break;
        }
    }
    return total;
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
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        CONF_F_DEF_LOAD_BIO;
        ERR_load_crypto_strings();
        SSL_load_error_strings();
    });

    SSL_CTX *ctx;
    ctx = SSL_CTX_new(SSLv23_client_method());
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }

    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
    return ctx;
}



std::once_flag SocketSSL::m_initializationFlag;
