//
// Created by ctuh on 12/16/22.
//

#include "JsonParser.hpp"

JsonParser::JsonParser(const std::string &jsonString): m_jsonString(jsonString) {}

std::optional<std::string> JsonParser::operator[](std::string const& fieldName) {
    if(m_fieldNameValue.find(fieldName) == m_fieldNameValue.end()) {
        auto pos = m_jsonString.find(fieldName);
        if(pos == std::string::npos) {
            m_fieldNameValue[fieldName] = {};
            return {};
        }

        auto beginOfValue = m_jsonString.substr(pos + fieldName.size()).find(':') + pos + fieldName.size() + 1;
        if(m_jsonString[beginOfValue] == '"')
            beginOfValue++;
        auto valueLength = m_jsonString.substr(beginOfValue).find('"');

        if(valueLength == std::string::npos) {
            m_fieldNameValue[fieldName] = {};
            return {};
        }

        if(m_jsonString[beginOfValue+valueLength-1] == '"')
            valueLength--;

        m_fieldNameValue[fieldName] = m_jsonString.substr(beginOfValue, valueLength);
        return m_fieldNameValue[fieldName];
    }
    return m_fieldNameValue[fieldName];
}