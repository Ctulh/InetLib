
#pragma once

#include <string>
#include <unordered_map>
#include <optional>

class JsonParser {
public:
    JsonParser(std::string const& jsonString);

public:
    std::optional<std::string> operator[](std::string const&);

private:
    std::string m_jsonString;
    std::unordered_map<std::string, std::optional<std::string>> m_fieldNameValue;
};