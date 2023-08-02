//
// Created by ctuh on 8/2/23.
//

#pragma once

#include <sys/socket.h>
#include <sys/types.h>

template<int level, int option, typename StructType>
class RAIISocketFlagsManipulator {
public:
    RAIISocketFlagsManipulator(int socketFd, StructType const& optionValue): m_socketFd(socketFd), m_structSize(sizeof(StructType)) {
        getsockopt(m_socketFd, level, option, &m_prevValue, &m_structSize);
        setsockopt(m_socketFd, level, option, &optionValue, m_structSize);
    }
    ~RAIISocketFlagsManipulator() {
        setsockopt(m_socketFd, level, option, &m_prevValue, m_structSize);
    }

private:
    socklen_t m_structSize;
    StructType m_prevValue;
    int m_socketFd;
};
