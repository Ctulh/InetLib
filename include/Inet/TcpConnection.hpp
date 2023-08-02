//
// Created by egor on 10/25/22.
//

#pragma once

#include "InetAddress.hpp"
#include "callbacks.hpp"
#include "Socket.hpp"
#include <memory>

class TcpConnection {
public:
    TcpConnection(InetAddress const& inetAddress);
    TcpConnection(int fd);
    TcpConnection(std::shared_ptr<Socket> socket);
    virtual ~TcpConnection();
public:
    virtual int send(const char* msg, std::size_t len) const;
    virtual int send(std::string_view msg) const;
    virtual int receive(char* msg, std::size_t len) const;
    virtual int receive(std::string& msg) const;

    virtual bool connect(int32_t timeoutSec = -1, int32_t timeoutUSec = -1);

    int getFd() const;
    void shutdown();

    bool isConnected() const;
protected:
    bool m_connected;
    SocketPtr m_socket;
};