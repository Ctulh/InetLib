//
// Created by ctuh on 12/8/22.
//

#pragma once

#include <string_view>
#include <map>

#include "HttpVersion.hpp"
#include "HttpMessage.hpp"
#include "HttpCookie.hpp"
#include "HttpMethod.hpp"

class HttpBuilder {
public:
    HttpBuilder();
    virtual ~HttpBuilder() = default;

public:
    virtual void setHttpMethod(HttpMethod httpMethod);
    virtual void setHttpVersion(HttpVersion httpVersion);
    virtual void setUri(std::string_view uri);
    virtual void setUserAgent(std::string_view userAgent);
    virtual void setAcceptLanguage(std::string_view acceptLanguage);
    virtual void setStatusCode(int statusCode);
    virtual void setDateTime(std::string_view dateTime);
    virtual void setCurrentDateTime();
    virtual void setLastModifiedDateTime(std::string_view lastModifiedDateTime);
    virtual void setServer(std::string_view server);
    virtual void setContentType(std::string_view contentType);
    virtual void setContentTypeFromFilename(std::string_view filename);
    virtual void setConnectionStatus(std::string_view connectionStatus);
    virtual void setBody(std::string_view body);
    virtual void addCookie(HttpCookie const& cookie);
protected:
    HttpMessage m_httpMessage;
    std::map<std::string, std::string> m_fileExtensionContentType;
    std::map<int, std::string> m_statusCodeDescription;
};