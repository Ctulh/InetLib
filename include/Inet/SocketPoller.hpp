//
// Created by egor on 11/8/22.
//

#pragma once

#include "StreamSocket.hpp"

#include <sys/epoll.h>
#include <map>

enum POLLER_EVENTS {
    CLOSE_CONNECTION = 1,
    RECEIVE_MESSAGE = 2,
    ERROR = -1,
};

class SocketPoller {
public:
    SocketPoller(int maxConnections, int timeout);
    ~SocketPoller();
public:
    void add(StreamSocketPtr);
    void remove(StreamSocketPtr);
    void poll();

    void setReceiveMessageOnSocketCallback(ReceiveMessageOnSocketCallback const&);
    void setReceiveMessageCallback(ReceiveMessageCallback const&);
    void setCloseConnectionCallback(CloseConnectionCallback const&);
private:
    ReceiveMessageOnSocketCallback m_receiveMessageOnSocketCallback;
    ReceiveMessageCallback m_receiveMessageCallback;
    CloseConnectionCallback m_closeConnectionCallback;

    int m_epollFd;
    int m_maxConnections;
    int m_timeout;
    std::vector<epoll_event> m_epollEvents;
    std::map<int, StreamSocketPtr> m_connections;
};
