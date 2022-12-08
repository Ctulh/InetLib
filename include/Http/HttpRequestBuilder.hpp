//
// Created by ctuh on 12/8/22.
//

#pragma once

#include "HttpBuilder.hpp"

class HttpRequestBuilder: public HttpBuilder {
public:
    HttpRequestBuilder() = default;
public:
    std::string getResult() const;
};