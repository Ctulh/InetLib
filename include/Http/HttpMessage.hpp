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
public:
    HttpMessage() = default;
    HttpMessage(HttpMessage const&) = default;

public:
    std::string uri;
    std::string body;
    std::string host;
    std::string accept;
    std::string server;
    std::string dateTime;
    std::string userAgent;
    std::string connection;
    std::string contentType;
    std::string lastModified;
    std::string acceptLanguage;
    std::string acceptEncoding;

    int statusCode;
    HttpVersion version;
    HttpMethod httpMethod;
    std::vector<HttpCookie> cookies;
};
