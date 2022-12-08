//
// Created by ctuh on 12/8/22.
//

#pragma once

#include <sstream>

class HttpCookie {
public:
    std::string getCookieString() const {
        std::stringstream ss;
        if(!cookieName.empty() and !cookieValue.empty())
            ss << "Cookie: " << cookieName << "=" << cookieValue;
        if(!cookieDomain.empty())
            ss << "; " << "Domain=" << cookieDomain;
        return ss.str();
    }
public:
    std::string cookieName;
    std::string cookieValue;
    std::string cookieDomain;
};