//
// Created by egor on 10/28/22.
//

#pragma once

#include "callbacks.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"

#include <memory>
#include <atomic>

class ConnectionAcceptor {
public:
    ConnectionAcceptor(InetAddress const&);
public:
    void setReceiveConnectionCallback(ReceiveConnectionCallback const&);
    void run();
    void stop();
    int fd() const;
private:
    int m_epollFd;
    std::atomic_flag m_isRunning;
    std::unique_ptr<Socket> m_socket;
    ReceiveConnectionCallback m_receiveConnectionCallback;
};