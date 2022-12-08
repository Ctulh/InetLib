//
// Created by egor on 10/25/22.
//

#include "TcpConnection.hpp"
#include <iostream>
#include <unistd.h>

TcpConnection::TcpConnection(std::shared_ptr<Socket> socket) {
    m_socket = std::move(socket);
    m_connected = true;
}

TcpConnection::~TcpConnection() {}

TcpConnection::TcpConnection(int fd) {
    m_socket = std::make_unique<Socket>(fd);
    m_connected = true;
}

void TcpConnection::send(const char *msg, std::size_t len) {
    auto result = write(m_socket->fd(), msg, len);
    std::cout << "Sent: " << result << '\n';
}

TcpConnection::TcpConnection(const InetAddress &inetAddress) {
    m_socket = std::make_unique<Socket>(inetAddress, SOCK_TYPE::TCP);
}

int TcpConnection::fd() const {
    return m_socket->fd();
}

void TcpConnection::shutdown() {
    m_socket->shutDown();
}

bool TcpConnection::isConnected() const {
    return m_connected;
}