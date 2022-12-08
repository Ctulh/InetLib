//
// Created by ctuh on 12/8/22.
//

#include "HttpMethod.hpp"

std::string httpMethodToString(HttpMethod method) {
    switch (method) {
        case HttpMethod::GET: return "GET";
        case HttpMethod::HEAD: return "HEAD";
        case HttpMethod::POST: return "POST";
        case HttpMethod::PUT: return "PUT";
        case HttpMethod::DELETE: return "DELETE";
        case HttpMethod::CONNECT: return "CONNECT";
        case HttpMethod::OPTIONS: return "OPTIONS";
        case HttpMethod::TRACE: return "TRACE";
        case HttpMethod::PATCH: return "PATCH";
    }
}