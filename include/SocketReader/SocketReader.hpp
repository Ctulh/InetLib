//
// Created by egor on 11/2/22.
//

#pragma once

#include <string>
#include <memory>
#include "Inet/Socket.hpp"
#include "Inet/StreamSocket.hpp"

enum READ_STATUS {
    GOT_MESSAGE = 1,
    EMPTY_MESSAGE = 2,
    CONNECTION_CLOSED = -1,
};

class SocketReader {
public:
    READ_STATUS read(StreamSocketPtr connection);
    std::string getBuffer();
    void clear();
private:
    std::string m_buffer;
};

using SocketReaderPtr = std::shared_ptr<SocketReader>;
