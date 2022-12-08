//
// Created by ctuh on 12/8/22.
//

#include "HttpRequestBuilder.hpp"

#include <sstream>

std::string HttpRequestBuilder::getResult() const {
    std::stringstream resultString;

    if(m_httpMessage.httpMethod != HttpMethod::NONE)
        resultString << httpMethodToString(m_httpMessage.httpMethod) << " ";
    if(!m_httpMessage.uri.empty())
        resultString << m_httpMessage.uri << " ";
    if(m_httpMessage.version.major != 0 && m_httpMessage.version.minor != 0)
        resultString << "HTTP/" << std::to_string(m_httpMessage.version.major) << '.' << std::to_string(m_httpMessage.version.minor) << "\r\n";
    if(not m_httpMessage.userAgent.empty())
        resultString << "User-Agent: "<< m_httpMessage.userAgent << "\r\n";
    if(not m_httpMessage.cookies.empty()) {
        for(auto const& cookie: m_httpMessage.cookies) {
            resultString << cookie.getCookieString() << "\r\n";
        }
    }
    if(not m_httpMessage.acceptLanguage.empty())
        resultString << "Accept-Language: "<< m_httpMessage.acceptLanguage << "\r\n";
    if(!m_httpMessage.connection.empty())
        resultString << "Connection: " << m_httpMessage.connection << "\r\n\r\n";

    return resultString.str();
}
