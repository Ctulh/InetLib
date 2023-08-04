//
// Created by egor on 10/25/22.
//

#include "StreamSocket.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>

namespace {
    constexpr uint32_t BUFFER_SIZE = 1024;
}

ssize_t StreamSocket::send(const char *msg, std::size_t len) const {
    return ::send(nativeHandle(), msg, len, 0);
}

ssize_t StreamSocket::send(std::string_view msg) const {
    return ::send(nativeHandle(), msg.data(), msg.size(), 0);
}

ssize_t StreamSocket::send(std::string const& msg) const {
    return ::send(nativeHandle(), msg.data(), msg.size(), 0);
}

ssize_t StreamSocket::receive(char *msg, std::size_t len) const {
    return ::read(nativeHandle(), msg, len);
}

ssize_t StreamSocket::receive(std::string &msg) const {
    int total;

    for(;;) {
        int result;
        char buf[BUFFER_SIZE];
        result = ::read(nativeHandle(), buf, BUFFER_SIZE);
        if(result == BUFFER_SIZE) {
            total += result;
            msg += buf;
            continue;
        }
        else if(result == 0)
            return total;
        else if(result == -1) {
            setError();
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

bool StreamSocket::connect() const {
    auto socketConnect = [&]() -> int {
        auto inetAddress = getInetAddress();
        return ::connect(nativeHandle(), inetAddress.getSockAddr(), sizeof(*inetAddress.getSockAddr()));
    };
    int result = socketConnect();
    if(result == -1) {
        setError();
        return false;
    }
    return true;
}
