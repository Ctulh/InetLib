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

int Socket::bind() {
    return ::bind(m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), sizeof(sockaddr));
}

int Socket::connect() {
    return ::connect(m_socketFd, m_inetAddress->getSockAddr(), sizeof (*m_inetAddress->getSockAddr()));
}

int Socket::recv(char *msg, int len) const {
    return readFromSock(m_socketFd, msg, len);
}

int Socket::recv(std::string &msg) const {
    int total;

    for(;;) {
        int result;
        char buf[BUFFER_SIZE];
        result = readFromSock(m_socketFd, buf, BUFFER_SIZE);
        if(result == BUFFER_SIZE) {
            total += result;
            msg += buf;
            continue;
        }
        else if(result == 0)
            return total;
        else if(result == -1) {
            std::cout << std::strerror(errno) << '\n';
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

int Socket::writeToSock(const char *msg, int len) const {
    if(m_sockConnectionType == SOCK_TYPE::TCP)
        return ::write(m_socketFd, msg, len);
    else {
        auto sockAddr = m_inetAddress->getSockAddr();
        return ::sendto(m_socketFd, msg, len, 0, sockAddr, sizeof(*sockAddr));
    }
}

int Socket::readFromSock(int fd, char *buf, int bufSize) const {
    if(m_sockConnectionType == SOCK_TYPE::TCP)
        return ::read(fd, buf, bufSize);
    else {
        struct sockaddr_in si_other;
        socklen_t slen = sizeof(si_other);
        return ::recvfrom(m_socketFd, buf, bufSize, 0,  (struct sockaddr *) &si_other, &slen);
    }
}

int Socket::send(const char *msg, int len) const {
    return writeToSock(msg, len);
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
