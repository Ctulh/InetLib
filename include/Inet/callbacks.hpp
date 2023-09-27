//
// Created by egor on 10/25/22.
//

#pragma once

#include <functional>
#include <memory>
#include "InetAddress.hpp"

class StreamSocket;
class SocketReader;

using StreamSocketPtr = std::shared_ptr<StreamSocket>;
using SocketReaderPtr = std::shared_ptr<SocketReader>;

using ReceiveMessageCallback = std::function<void(InetAddress const&, std::vector<std::byte> const&)>;
using ReceiveMessageOnSocketCallback = std::function<void(StreamSocketPtr, SocketReaderPtr)>;
using SendMessageCallback = std::function<void(StreamSocketPtr)>;
using ReceiveConnectionCallback = std::function<void(int)>;
using CloseConnectionCallback = std::function<void(StreamSocketPtr)>;
