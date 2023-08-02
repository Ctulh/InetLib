//
// Created by ctuh on 12/13/22.
//

#pragma once

#include <string>

class ISocket {
public:
    ~ISocket() = default;

public:
    virtual int bind() const = 0;
    virtual int listen() const = 0;
    virtual int accept() const = 0;

    virtual int fd() const = 0;

    virtual int receive(char* msg, int len) const = 0;
    virtual int receive(std::string& msg) const = 0;
    virtual int send(const char* msg, int len) const = 0;

    virtual void shutDown() = 0;
};
