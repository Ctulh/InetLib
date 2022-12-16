//
// Created by ctuh on 12/12/22.
//

#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class HttpParser {
public:
    HttpParser(std::string const& message);

public:
    std::optional<std::string> operator[](std::string const& fieldName);

private:
    std::string m_message;
    std::unordered_map<std::string, std::optional<std::string>> m_fieldValue;
};
