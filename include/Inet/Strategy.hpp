//
// Created by ctuh on 12/8/22.
//

#pragma once

#include "StreamSocket.hpp"
#include "SocketReader/SocketReader.hpp"

class Strategy {
public:
    virtual ~Strategy() = default;
public:
    virtual void onReceiveMessage(TcpConnectionPtr connection, SocketReaderPtr socketReader) = 0;
    virtual void setCloseConnectionCallback(CloseConnectionCallback closeConnectionCallback) = 0;
};