//
// Created by ctuh on 11/24/22.
//

#pragma once

#include <string>
#include <vector>

#include "HttpVersion.hpp"
#include "HttpMethod.hpp"
#include "HttpCookie.hpp"

struct HttpMessage {
    HttpMessage() = default;
    HttpMessage(HttpMessage const&) = default;
public:
    HttpMethod httpMethod;
    HttpVersion version;
    int statusCode;
    std::string userAgent;
    std::string acceptLanguage;
    std::string uri;
    std::string dateTime;
    std::string server;
    std::string contentType;
    std::string connection;
    std::string body;
    std::string lastModified;
    std::vector<HttpCookie> cookies;
};
