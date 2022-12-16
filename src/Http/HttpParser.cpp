//
// Created by ctuh on 12/16/22.
//

#include "HttpParser.hpp"
#include <algorithm>

HttpParser::HttpParser(const std::string &message): m_message(message) {}

std::optional<std::string> HttpParser::operator[](std::string const& fieldName) {
    if(m_fieldValue.find(fieldName) == m_fieldValue.end()) {
        auto pos = m_message.find(fieldName);
        if(pos == std::string::npos) {
            m_fieldValue[fieldName] = {};
            return {};
        }

        auto beginOfValue = pos + fieldName.size() + 1;
        auto endOfValue = m_message.substr(beginOfValue).find("\r\n") + beginOfValue;

        if(endOfValue == std::string::npos) {
            m_fieldValue[fieldName] = {};
            return {};
        }

        m_fieldValue[fieldName] = m_message.substr(beginOfValue, endOfValue);
        return m_fieldValue[fieldName];
    }
}

