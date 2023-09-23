//
// Created by egor on 11/2/22.
//

#include "SocketReader.hpp"


READ_STATUS SocketReader::read(StreamSocketPtr connection) {
    connection->setReceiveTimeout(std::chrono::milliseconds(10000));
    std::size_t result = connection->receive(m_buffer);
    if(result == 0)
        return READ_STATUS::EMPTY_MESSAGE;
    return READ_STATUS::GOT_MESSAGE;
}

std::string SocketReader::getBuffer() {
    return m_buffer;
}

void SocketReader::clear() {
    m_buffer.clear();
}