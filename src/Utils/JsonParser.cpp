//
// Created by ctuh on 12/16/22.
//

#include "JsonParser.hpp"
#include <stack>

JsonParser::JsonParser(const std::string &jsonString): m_jsonString(jsonString) {}

std::optional<std::string> JsonParser::operator[](std::string const& fieldName) {
    auto it = m_fieldNameValue.find(fieldName);
    if(it != m_fieldNameValue.end())
        return it->second;


    auto beginPos = m_jsonString.find(fieldName);
    if(beginPos == std::string::npos) {
        m_fieldNameValue[fieldName] = {};
        return {};
    }
    beginPos += fieldName.size();
    beginPos += 2; // because of " and :

    std::stack<char> bracketDuty;

    std::string value;
    for(auto i = beginPos; i < m_jsonString.size(); i++) {
        auto symbol = m_jsonString[i];
        if(symbol == '[') {
            bracketDuty.push(symbol);
            continue;
        }
        else if(symbol == '"' && !bracketDuty.empty() && bracketDuty.top() == '"') {
            bracketDuty.pop();
        }
        else if(symbol == '"') {
            bracketDuty.push(symbol);
        }
        else if(symbol == ']' && !bracketDuty.empty() && bracketDuty.top() == '[') {
            bracketDuty.pop();
        }
        else if(symbol == ',' && !bracketDuty.empty()) {
            value += symbol;
        }
        else if(symbol == ',' && bracketDuty.empty()) {
            break;
        }
        else if(symbol == ' ' && (bracketDuty.empty() || bracketDuty.top() =='[')) {
            continue;
        }
        else {
            value += symbol;
            continue;
        }
        if(bracketDuty.empty())
            break;
    }
    m_fieldNameValue[fieldName] = value;
    return value;
}