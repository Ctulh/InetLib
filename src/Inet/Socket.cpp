//
// Created by egor on 10/13/22.
//

#include "Socket.hpp"
#include <string>
#include <iostream>
#include <cstring>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "RAIISocketFlagsManipulator.hpp"
#include "SocketFlagsManipulator.hpp"
#include "Error.hpp"

namespace {
    constexpr int BUFFER_SIZE = 1024;
}


Socket::Socket(int fd) {
    m_socketFd = fd;
}

Socket::~Socket() {
    shutdown(m_socketFd, SHUT_RDWR);
}

bool Socket::accept() const {
    socklen_t addrLength = sizeof(sockaddr_in);
    int result = ::accept ( m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), &addrLength);
    return result != -1;
}

bool Socket::listen() const {
    int result = ::listen(m_socketFd, SOMAXCONN);
    return result != -1;
}

bool Socket::bind() const {
    int result = ::bind(m_socketFd, (sockaddr*)m_inetAddress->getSockAddr(), sizeof(sockaddr));
    return result != -1;
}

int Socket::nativeHandle() const {
    return m_socketFd;
}

bool Socket::shutDown(int how) {
    m_isConnected = false;
    int result = ::shutdown(m_socketFd, how);
    if(result != -1) {
        setError();
    }
    return result != -1;
}

bool Socket::setNonBlocking() {
    int flags = getFlags();
    int result = fcntl(m_socketFd, F_SETFL, flags | O_NONBLOCK);
    if(result == -1) {
        setError();
        return false;
    }
    return true;
}

bool Socket::isNonBlocking() const {
    int flags = getFlags();
    if(flags == -1)
        return false;
    if((flags & O_NONBLOCK) == 0)
        return false;
    return true;
}

int Socket::getFlags() const {
    int flags = fcntl(m_socketFd, F_GETFL);
    if(flags == -1)
        setError();
    return flags;
}

bool Socket::setFlag(int flag, bool shouldEnable) {
    int flags = getFlags();
    if(flags == -1) {
        return false;
    }
    if(shouldEnable) {
        flags = flags | flag;
    }
    else {
        flags = flags & ~flag;
    }
    return setFlags(flags);
}

bool Socket::setFlags(int flags) {
    int result = ::fcntl(m_socketFd, F_SETFL, flags);
    if(result == -1) {
        setError();
        return false;
    }
    return true;
}

bool Socket::setConnectTimeout(std::chrono::milliseconds connectTimeout) {
    return setSendTimeout(connectTimeout);
}

bool Socket::setSendTimeout(std::chrono::milliseconds sendTimeout) {
    timeval timeout {};
    long int count = sendTimeout.count();
    timeout.tv_sec = count / 1000;
    timeout.tv_usec = count % 1000;
    bool result = SocketFlagsManipulator<SOL_SOCKET, SO_SNDTIMEO, timeval>::setFlag(m_socketFd, timeout);
    if(!result) {
        setError();
    }
    return result;
}

bool Socket::setReceiveTimeout(std::chrono::milliseconds receiveTimeout) {
    timeval timeout {};
    long int count = receiveTimeout.count();
    timeout.tv_sec = count / 1000;
    timeout.tv_usec = count % 1000;
    bool result = SocketFlagsManipulator<SOL_SOCKET, SO_RCVTIMEO, timeval>::setFlag(m_socketFd, timeout);
    if(!result) {
        setError();
    }
    return result;
}

void Socket::setError() const {
    m_lastError = Error::getLastError();
}

int Socket::getLastError() const {
    return m_lastError;
}

InetAddress Socket::getInetAddress() const {
    return *m_inetAddress;
}
