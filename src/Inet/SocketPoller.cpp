//
// Created by egor on 11/8/22.
//

#include "SocketPoller.hpp"
#include "SocketReader/SocketReader.hpp"

#include <sys/epoll.h>
#include <iostream>


SocketPoller::SocketPoller(int maxConnections, int timeout): m_maxConnections(maxConnections),
                                                             m_timeout(timeout),
                                                             m_epollEvents(maxConnections) {
    m_epollFd = epoll_create(maxConnections);
}

void SocketPoller::add(TcpConnectionPtr connection) {
    struct epoll_event ev;

    ev.data.fd = connection->fd();
    ev.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(m_epollFd, EPOLL_CTL_ADD, connection->fd(), &ev) == -1) {
        std::cout << "ERROR Adding epoll: "<< connection->fd() << '\n';
    }
    m_connections.insert(std::pair<int, TcpConnectionPtr>(connection->fd(), connection));
}

void SocketPoller::remove(TcpConnectionPtr connection) {
    m_connections.erase(connection->fd());
    if(epoll_ctl(m_epollFd, EPOLL_CTL_DEL, connection->fd(), nullptr) == ENOENT) {
        std::cout << "ERROR Removing epoll: "<< connection->fd() << '\n';
    }
}

void SocketPoller::poll() {
    auto readyAmount = epoll_wait(m_epollFd, m_epollEvents.data(), m_maxConnections, -1);
    for(int i = 0; i < readyAmount; i++) {
        if(m_epollEvents[i].events & EPOLLIN) {
            SocketReaderPtr socketReader = std::make_shared<SocketReader>();
            auto result = socketReader->read(m_connections[m_epollEvents[i].data.fd]);
            if(result == READ_STATUS::GOT_MESSAGE)
                m_receiveMessageCallback(m_connections.at(m_epollEvents[i].data.fd), socketReader);
        }
    }
}

void SocketPoller::setCloseConnectionCallback(CloseConnectionCallback const& closeConnectionCallback) {
    m_closeConnectionCallback = closeConnectionCallback;
}

void SocketPoller::setReceiveMessageCallback(ReceiveMessageCallback const& receiveMessageCallback) {
    m_receiveMessageCallback = receiveMessageCallback;
}


SocketPoller::~SocketPoller() = default;
