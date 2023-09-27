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

void SocketPoller::add(StreamSocketPtr connection) {
    if(!connection)
        return;
    struct epoll_event ev;

    ev.data.fd = connection->nativeHandle();
    ev.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(m_epollFd, EPOLL_CTL_ADD, connection->nativeHandle(), &ev) == -1) {
        std::cout << "ERROR Adding epoll: "<< connection->nativeHandle() << '\n';
    }
    m_connections.insert(std::pair<int, StreamSocketPtr>(connection->nativeHandle(), connection));
}

void SocketPoller::remove(StreamSocketPtr connection) {
    m_connections.erase(connection->nativeHandle());
    if(epoll_ctl(m_epollFd, EPOLL_CTL_DEL, connection->nativeHandle(), nullptr) == ENOENT) {
        std::cout << "ERROR Removing epoll: "<< connection->nativeHandle() << '\n';
    }
}

void SocketPoller::poll() {
    auto readyAmount = epoll_wait(m_epollFd, m_epollEvents.data(), m_maxConnections, m_timeout);
    for(int i = 0; i < readyAmount; i++) {
        if(m_epollEvents[i].events & EPOLLIN) {
            std::vector<std::byte> msg;
            auto result = m_connections[m_epollEvents[i].data.fd]->receive(msg);
            if(result > 0) {
                if (m_receiveMessageCallback.has_value())
                    m_receiveMessageCallback.value()(m_connections[m_epollEvents[i].data.fd]->getInetAddress(), msg);
            }
        }
    }
}

void SocketPoller::setReceiveMessageOnSocketCallback(ReceiveMessageOnSocketCallback const& receiveMessageOnSocketCallback) {
    m_receiveMessageOnSocketCallback = receiveMessageOnSocketCallback;
}

void SocketPoller::setCloseConnectionCallback(CloseConnectionCallback const& closeConnectionCallback) {
    m_closeConnectionCallback = closeConnectionCallback;
}

void SocketPoller::setReceiveMessageCallback(ReceiveMessageCallback const& receiveMessageCallback) {
    m_receiveMessageCallback = receiveMessageCallback;
}


SocketPoller::~SocketPoller() = default;
