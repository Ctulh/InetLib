//
// Created by egor on 11/2/22.
//


#include <future>
#include <sys/socket.h>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <unistd.h>

#include "SocketReader.hpp"

namespace {
    constexpr int BUFFER_SIZE = 1024;
}

READ_STATUS SocketReader::read(int fd) {
    int result;
    for(;;) {
        char buf[BUFFER_SIZE];
        result = ::read(fd, buf, BUFFER_SIZE);
        if(result == BUFFER_SIZE) {
            m_buffer += buf;
            continue;
        }
        else if(result == 0)
            return ::CONNECTION_CLOSED;
        else if(result == -1) {
            std::cout << std::strerror(errno) << '\n';
            return ::CONNECTION_CLOSED;
        }
        else if(result < BUFFER_SIZE) {
            m_buffer += buf;
            break;
        }
    }

    std::cout << result << '\n';

    if(!m_buffer.empty())
        return ::GOT_MESSAGE;
    return ::EMPTY_MESSAGE;
}

std::string SocketReader::getBuffer() {
    return m_buffer;
}

void SocketReader::clear() {
    m_buffer.clear();
}