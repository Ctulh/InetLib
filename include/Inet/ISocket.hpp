//
// Created by ctuh on 12/13/22.
//

#pragma once

#include <string>

class ISocket {
public:
    ~ISocket() = default;

public:
    virtual int bind() = 0;
    virtual int listen() = 0;
    virtual int accept() = 0;

    virtual int fd() const = 0;

    virtual int recv(char* msg, int len) const = 0;
    virtual int recv(std::string& msg) const = 0;
    virtual int send(const char* msg, int len) const = 0;

    virtual void shutDown() = 0;
};
