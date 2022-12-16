//
// Created by ctuh on 12/8/22.
//
#include "HttpBuilder.hpp"

#include <iostream>
#include <iomanip>

HttpBuilder::HttpBuilder(): m_fileExtensionContentType({
                                                               {".html", "text/html"},
                                                               {".css", "text/css"}
                                                       }) // TODO load from config
{
    m_statusCodeDescription.insert({200, "OK"});
}

void HttpBuilder::setHttpMethod(HttpMethod httpMethod) {
    m_httpMessage.httpMethod = httpMethod;
}

void HttpBuilder::setHttpVersion(HttpVersion httpVersion) {
    m_httpMessage.version = httpVersion;
}

void HttpBuilder::setStatusCode(int statusCode) {
    m_httpMessage.statusCode = statusCode;
}

void HttpBuilder::setDateTime(std::string_view dateTime) {
    m_httpMessage.dateTime = dateTime;
}

void HttpBuilder::setCurrentDateTime() {
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    m_httpMessage.dateTime = oss.str();
}

void HttpBuilder::setLastModifiedDateTime(std::string_view lastModifiedDateTime) {
    m_httpMessage.lastModified = lastModifiedDateTime;
}

void HttpBuilder::setServer(std::string_view server) {
    m_httpMessage.server = server;
}

void HttpBuilder::setContentType(std::string_view contentType) {
    m_httpMessage.contentType = contentType;
}

void HttpBuilder::setContentTypeFromFilename(std::string_view filename) {
    auto it =  filename.find_last_of('.');
    std::string fileExtension (filename.substr(it, filename.size()));

    if(auto contentType = m_fileExtensionContentType[fileExtension];
            !contentType.empty()) {
        m_httpMessage.contentType = contentType;
    } else {
        std::cout << "Cannot find contentType for " << filename << '\n';
    }
}

void HttpBuilder::setUserAgent(std::string_view userAgent) {
    m_httpMessage.userAgent = userAgent;
}

void HttpBuilder::setAcceptLanguage(std::string_view acceptLanguage) {
    m_httpMessage.acceptLanguage = acceptLanguage;
}

void HttpBuilder::setUri(std::string_view uri) {
    m_httpMessage.uri = uri;
}

void HttpBuilder::setConnectionStatus(std::string_view connectionStatus) {
    m_httpMessage.connection = connectionStatus;
}

void HttpBuilder::setBody(std::string_view body) {
    m_httpMessage.body = body;
}

void HttpBuilder::addCookie(HttpCookie const& cookie) {
    m_httpMessage.cookies.push_back(cookie);
}

void HttpBuilder::setAcceptEncoding(std::string_view acceptEncoding) {
    m_httpMessage.acceptEncoding = acceptEncoding;
}

void HttpBuilder::setAccept(std::string_view accept) {
    m_httpMessage.accept = accept;
}

void HttpBuilder::setHost(std::string_view host) {
    m_httpMessage.host = host;
}

void HttpBuilder::addField(std::string_view fieldName, std::string_view fieldValue) {
    m_httpMessage.fields.emplace_back(fieldName, fieldValue);
}
