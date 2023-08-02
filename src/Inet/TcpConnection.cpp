//
// Created by egor on 10/25/22.
//

#include "TcpConnection.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>

TcpConnection::TcpConnection(std::shared_ptr<Socket> socket) {
    m_socket = std::move(socket);
    m_connected = true;
}

TcpConnection::~TcpConnection() {}

TcpConnection::TcpConnection(int fd) {
    m_socket = std::make_unique<Socket>(fd);
    m_connected = true;
}

int TcpConnection::send(const char *msg, std::size_t len) const {
    return m_socket->send(msg, len);
}

int TcpConnection::send(std::string_view msg) const {
    return m_socket->send(msg.data(), msg.size());
}

int TcpConnection::receive(char *msg, std::size_t len) const {
    return m_socket->receive(msg, len);
}

int TcpConnection::receive(std::string &msg) const {
    return m_socket->receive(msg);
}

bool TcpConnection::connect(int32_t timeoutSec, int32_t timeoutUSec) {
    return m_socket->connect(timeoutSec, timeoutUSec);
}

TcpConnection::TcpConnection(const InetAddress &inetAddress) {
    m_socket = std::make_unique<Socket>(inetAddress, SOCK_TYPE::TCP);
}

int TcpConnection::getFd() const {
    return m_socket->fd();
}

void TcpConnection::shutdown() {
    m_socket->shutDown();
}

bool TcpConnection::isConnected() const {
    return m_socket->isConnected();
}