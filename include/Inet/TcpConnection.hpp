//
// Created by egor on 10/25/22.
//

#pragma once

#include "InetAddress.hpp"
#include "callbacks.hpp"
#include "Socket.hpp"
#include <cstdio>
#include <memory>

class TcpConnection {
public:
    TcpConnection(InetAddress const& inetAddress);
    TcpConnection(int fd);
    TcpConnection(std::shared_ptr<Socket> socket);
    ~TcpConnection();
public:
    void send(const char* msg, std::size_t len);
    void recv(std::string& msg);

    int fd() const;
    void shutdown();

    bool isConnected() const;
public:
private:
    bool m_connected;
    std::shared_ptr<Socket> m_socket;
};