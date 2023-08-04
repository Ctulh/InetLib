//
// Created by egor on 10/25/22.
//

#pragma once

#include "InetAddress.hpp"
#include "callbacks.hpp"
#include "Socket.hpp"
#include <memory>
#include <chrono>

class StreamSocket: public Socket {
    using base = Socket;
    static const SocketType StreamCommunication = SocketType::TCP;

public:
    StreamSocket(InetAddress const& inetAddress): base(inetAddress, StreamCommunication) {}
    StreamSocket(int fd): base(fd) {}

public:
    ssize_t send(const char* msg, std::size_t len) const;
    ssize_t send(std::string_view msg) const;
    ssize_t send(std::string const& msg) const;
    ssize_t receive(char* msg, std::size_t len) const;
    ssize_t receive(std::string& msg) const;
    bool connect() const;

private:

};