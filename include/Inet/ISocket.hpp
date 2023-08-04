//
// Created by ctuh on 12/13/22.
//

#pragma once

#include <string>
#include <chrono>

#include "InetAddress.hpp"

class ISocket {
public:
    virtual ~ISocket() = default;

public:
    virtual bool bind() const = 0;
    virtual bool listen() const = 0;
    virtual bool accept() const = 0;
    //virtual bool connect() = 0;

    virtual int nativeHandle() const = 0;

   // virtual int receive(char* msg, int len) const = 0;
    //virtual int receive(std::string& msg) const = 0;
    //virtual int send(const char* msg, int len) const = 0;

    virtual bool isNonBlocking() const = 0;
    virtual bool setNonBlocking() = 0;

    virtual int getFlags() const = 0;
    virtual bool setFlag(int flag, bool shouldEnable) = 0;
    virtual bool setFlags(int flags) = 0;

    virtual bool setConnectTimeout(std::chrono::milliseconds connectTimeout) = 0;
    virtual bool setSendTimeout(std::chrono::milliseconds sendTimeout) = 0;
    virtual bool setReceiveTimeout(std::chrono::milliseconds receiveTimeout) = 0;

    virtual int getLastError() const = 0;
    virtual InetAddress getInetAddress() const = 0;

    virtual bool shutDown(int how) = 0;
};
