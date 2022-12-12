//
// Created by egor on 10/13/22.
//

#include "Socket.hpp"
#include <string>
#include <iostream>
#include <cstring>
#include <sys/fcntl.h>

namespace {
    constexpr int BUFFER_SIZE = 1024;
}


Socket::Socket(int fd) {
    m_socketFd = fd;
}

Socket::~Socket() {
    shutdown(m_socketFd, 2);
}

int Socket::accept() {
    socklen_t addrLength = sizeof(sockaddr_in);
    return ::accept ( m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), &addrLength);
}

int Socket::listen() {
    return ::listen(m_socketFd, SOMAXCONN);
}

bool Socket::bind() {
    int bind_return = ::bind(m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), sizeof(sockaddr));
    if(bind_return == -1) {
        return false;
    }
    return true;
}

bool Socket::connect() {
    int status;
    status = ::connect(m_socketFd, m_inetAddress->getSockAddr(), sizeof (*m_inetAddress->getSockAddr()));

    if ( status == 0 ) {
        m_isConnected = true;
        return true;
    }
    return false;
}

int Socket::recv(char *msg, int len) const {
    return ::read(m_socketFd, msg, len);
}

int Socket::recv(std::string &msg) const {
    int result;
    for(;;) {
        char buf[BUFFER_SIZE];
        result = ::read(m_socketFd, buf, BUFFER_SIZE);
        if(result == BUFFER_SIZE) {
            msg += buf;
            continue;
        }
        else if(result == 0)
            return result;
        else if(result == -1) {
            std::cout << std::strerror(errno) << '\n';
            return result;
        }
        else if(result < BUFFER_SIZE) {
            msg += buf;
            break;
        }
    }
    return result;
}

int Socket::send(const char *msg, int len) const {
    return ::write(m_socketFd, msg, len);
}

int Socket::fd() const {
    return m_socketFd;
}

bool Socket::isConnected() const {
    return m_isConnected;
}

void Socket::shutDown() {
    m_isConnected = false;
    close(m_socketFd);
}

bool Socket::setNonBlocking() const {
    int flags = fcntl(m_socketFd, F_GETFL);
    auto result = fcntl(m_socketFd, F_SETFL,flags | O_NONBLOCK);
    return (result != -1);
}
