//
// Created by ctuh on 11/24/22.
//

#include <iostream>
#include <sstream>

#include "HttpResponseBuilder.hpp"

std::string HttpResponseBuilder::getResult() const {
    std::stringstream resultString;

    if(m_httpMessage.version.major != 0 && m_httpMessage.version.minor != 0)
        resultString << "HTTP/" << std::to_string(m_httpMessage.version.major) << '.' << std::to_string(m_httpMessage.version.minor) << ' ';
    if(m_httpMessage.statusCode != 0)
        resultString << std::to_string(m_httpMessage.statusCode) << ' ' << m_statusCodeDescription.at(m_httpMessage.statusCode) << '\n';
    if(!m_httpMessage.dateTime.empty())
        resultString << "Date: " << m_httpMessage.dateTime << '\n';
    if(!m_httpMessage.server.empty())
        resultString << "Server: " << m_httpMessage.server << '\n';
    if(!m_httpMessage.lastModified.empty())
        resultString << "Last-Modified: " << m_httpMessage.lastModified << '\n';

    resultString << "Content-Length: " << std::to_string(m_httpMessage.body.size()) << '\n';

    if(!m_httpMessage.contentType.empty())
        resultString << "Content-Type: " << m_httpMessage.contentType << '\n';
    if(!m_httpMessage.connection.empty())
        resultString << "Connection: " << m_httpMessage.connection << "\r\n\r\n";

    resultString << m_httpMessage.body;

    return resultString.str();
}