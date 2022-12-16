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
private:
    std::string getVersionString() const;
    std::string getUriString() const;
    std::string getMethodString() const;
    std::string getUserAgentString() const;
    std::string getContentTypeString() const;
    std::string getCookiesString() const;
    std::string getAcceptLanguageString() const;
    std::string getConnectionString() const;
    std::string getAcceptEncodingString() const;
    std::string getAcceptString() const;
    std::string getHostString() const;
    std::string getFields() const;
    std::string getContentLengthString(std::string const& body) const;
};