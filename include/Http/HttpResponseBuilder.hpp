//
// Created by egor on 11/15/22.
//

#pragma once

#include "HttpBuilder.hpp"

class HttpResponseBuilder: public HttpBuilder {
public:
    HttpResponseBuilder();
public:
    std::string getResult() const;
};