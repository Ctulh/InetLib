//
// Created by ctuh on 12/8/22.
//

#include "HttpRequestBuilder.hpp"

#include <sstream>

std::string HttpRequestBuilder::getResult() const {
    std::stringstream resultString;

    resultString << getMethodString() <<
                 getUriString() <<
                 getVersionString() <<
                 getHostString() <<
                 getAcceptEncodingString() <<
                 getAcceptString() <<
                 getUserAgentString() <<
                 getContentTypeString() <<
                 getAcceptLanguageString() <<
                 getConnectionString() <<
                 getCookiesString() << "\r\n";

    return resultString.str();
}

std::string HttpRequestBuilder::getMethodString() const {
    if(m_httpMessage.httpMethod != HttpMethod::NONE)
        return httpMethodToString(m_httpMessage.httpMethod) + " ";
    return "GET ";
}

std::string HttpRequestBuilder::getUriString() const {
    if(!m_httpMessage.uri.empty())
        return m_httpMessage.uri + " ";
    return "/ ";
}

std::string HttpRequestBuilder::getVersionString() const {
    std::stringstream resultString;
    resultString << "HTTP/";
    if(m_httpMessage.version.major != 0 && m_httpMessage.version.minor != 0)
         resultString << std::to_string(m_httpMessage.version.major) << '.' << std::to_string(m_httpMessage.version.minor);
    else
        resultString << "1.1";
    resultString << "\r\n";
    return resultString.str();
}

std::string HttpRequestBuilder::getUserAgentString() const {
    if(not m_httpMessage.userAgent.empty())
        return "User-Agent: " + m_httpMessage.userAgent + "\r\n";
    return "";
}

std::string HttpRequestBuilder::getContentTypeString() const {
    if(not m_httpMessage.contentType.empty())
        return "Content-Type: " + m_httpMessage.contentType + "\r\n";
    return "";
}

std::string HttpRequestBuilder::getCookiesString() const {
    std::stringstream resultString;
    if(not m_httpMessage.cookies.empty()) {
        resultString << "Cookie: ";
        for(auto const& cookie: m_httpMessage.cookies) {
            resultString << cookie.getCookieString();
        }
        resultString << "\r\n";
    }
    return resultString.str();
}

std::string HttpRequestBuilder::getAcceptLanguageString() const {
    std::stringstream resultString;
    if(not m_httpMessage.acceptLanguage.empty())
        resultString << "Accept-Language: " << m_httpMessage.acceptLanguage << "\r\n";;
    return resultString.str();
}

std::string HttpRequestBuilder::getConnectionString() const {
    std::stringstream resultString;
    resultString << "Connection: ";
    if(not m_httpMessage.connection.empty())
        resultString << m_httpMessage.connection;
    else
        resultString << "keep-alive";
    resultString << "\r\n";
    return resultString.str();
}

std::string HttpRequestBuilder::getAcceptEncodingString() const {
    if(not m_httpMessage.acceptEncoding.empty()) {
        return "Accept-Encoding: " + m_httpMessage.acceptEncoding + "\r\n";
    }
    return "";
}

std::string HttpRequestBuilder::getAcceptString() const {
    if(not m_httpMessage.accept.empty()) {
        return "Accept: " + m_httpMessage.accept + "\r\n";
    }
    return "";
}

std::string HttpRequestBuilder::getHostString() const {
    if(not m_httpMessage.host.empty()) {
        return "Host: " + m_httpMessage.host + "\r\n";
    }
    return "";
}
