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
    std::size_t send(const char* msg, std::size_t len) const;
    std::size_t send(std::string_view msg) const;
    std::size_t send(std::string const& msg) const;
    std::size_t send(std::vector<std::byte> const& msg) const;
    std::size_t receive(char* msg, std::size_t len) const;
    std::size_t receive(std::string& msg) const;
    std::size_t receive(std::vector<std::byte>& msg) const;
    bool connect() const;

private:

};