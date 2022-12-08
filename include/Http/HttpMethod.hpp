//
// Created by ctuh on 12/8/22.
//

#pragma once

#include <string>

enum class HttpMethod {
    NONE,
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH
};

std::string httpMethodToString(HttpMethod method);