//
// Created by egor on 10/25/22.
//

#pragma once

#include <functional>
#include <memory>

class TcpConnection;
class SocketReader;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using SocketReaderPtr = std::shared_ptr<SocketReader>;

using ReceiveMessageCallback = std::function<void(TcpConnectionPtr, SocketReaderPtr)>;
using SendMessageCallback = std::function<void(TcpConnectionPtr)>;
using ReceiveConnectionCallback = std::function<void(int)>;
using CloseConnectionCallback = std::function<void(TcpConnectionPtr)>;
