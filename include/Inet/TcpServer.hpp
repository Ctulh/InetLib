//
// Created by egor on 10/13/22.
//

#pragma once

#include "InetAddress.hpp"
#include "TcpConnection.hpp"
#include "ConnectionAcceptor.hpp"
#include "SocketReader/SocketReader.hpp"
#include "Strategy.hpp"
#include "SocketPoller.hpp"
#include "callbacks.hpp"

#include <iostream>
#include <atomic>
#include <functional>
#include <thread>
#include <set>
#include <utility>

class TcpServer {
public:
    TcpServer(const InetAddress& inet, Strategy* strategy):
                                  m_inetAddress(inet), m_strategy(std::move(strategy)) {
        m_connectionAcceptor = std::make_unique<ConnectionAcceptor>(m_inetAddress);
        m_connectionAcceptor->setReceiveConnectionCallback(std::bind(&TcpServer::acceptConnectionCallback, this, std::placeholders::_1));
        m_socketPoller = std::make_unique<SocketPoller>(10, 100);
        m_socketPoller->setReceiveMessageCallback([this](TcpConnectionPtr connection, SocketReaderPtr socketReader){this->m_strategy->onReceiveMessage(connection, socketReader);});
        m_socketPoller->setCloseConnectionCallback([this](TcpConnectionPtr connection){this->connectionClosed(connection);});
        m_strategy->setCloseConnectionCallback([this](TcpConnectionPtr const& conn) {this->connectionClosed(conn);});
    }

    ~TcpServer() {
        for(auto& connection: m_connections) {
            connection->shutdown();
        }
    }

    void run() {
        m_isRunning.test_and_set();

        std::thread t1 ([this](){m_connectionAcceptor->run();});
        t1.detach();

        while(m_isRunning.test()) {

            if (m_isCanPoll.test())
                m_socketPoller->poll();
        }

        m_connectionAcceptor->stop();
    }

    void stop() {
        m_isRunning.clear();
        m_connectionAcceptor->stop();
    }

private:
    void connectionClosed(TcpConnectionPtr const& connection) {

        m_isCanPoll.clear();

        std::cout << "Close connection: " << connection->fd() << '\n';
        connection->shutdown();
        m_socketPoller->remove(connection);
        m_connections.erase(connection);

        m_isCanPoll.test_and_set();

    }
    void acceptConnectionCallback(int fd) {
        auto newConnection = std::make_shared<TcpConnection>(std::make_shared<Socket>(fd));
        if(newConnection) {
            std::cout << "Got new connection: " << fd << '\n';
        }

        m_isCanPoll.clear();

        m_connections.insert(m_connections.end(), newConnection);
        m_socketPoller->add(newConnection);

        m_isCanPoll.test_and_set();
    }

private:
    Strategy* m_strategy;
    std::atomic_flag m_isRunning;
    std::atomic_flag m_isCanPoll;
    std::unique_ptr<ConnectionAcceptor> m_connectionAcceptor;
    std::unique_ptr<SocketPoller> m_socketPoller;
    std::set<TcpConnectionPtr> m_connections;
    InetAddress m_inetAddress;
};