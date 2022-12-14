#include <iostream>

#include "include/Http/HttpBuilder.hpp"
#include "HttpRequestBuilder.hpp"
#include "HttpCookie.hpp"
#include "Inet/Socket.hpp"
#include "Inet/TcpConnection.hpp"
#include "SocketReader/SocketReader.hpp"
#include "Inet/SocketSSL.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>

class XiaomiCloudConnector {
public:
    XiaomiCloudConnector(std::string login, std::string password) {
        m_login = login;
        m_password = password;

        m_agent = generateAgent();
        m_deviceId = generateDeviceId();
    }

    bool login() {

        m_requestBuilder.addCookie({.cookieName= "sdkVersion", .cookieValue = "accountsdk-18.8.15", .cookieDomain = "mi.com"});
        m_requestBuilder.addCookie({.cookieName= "sdkVersion", .cookieValue = "accountsdk-18.8.15", .cookieDomain = "xiaomi.com"});
        m_requestBuilder.addCookie({.cookieName= "deviceId", .cookieValue = m_deviceId, .cookieDomain = "mi.com"});
        m_requestBuilder.addCookie({.cookieName= "deviceId", .cookieValue = m_deviceId, .cookieDomain = "xiaomi.com"});

        loginFirstStep();
    }

private:

    bool loginFirstStep() {
        HttpRequestBuilder builder;
        builder.setHttpMethod(HttpMethod::GET);
        builder.setUri("/pass/serviceLogin?sid=xiaomiio&_json=true");
        builder.setUserAgent(generateAgent());
        builder.setHost("account.xiaomi.com");
        builder.setContentType("application/x-www-form-urlencoded");
        builder.setAcceptEncoding("gzip, deflate");
        builder.setAccept("*/*");
        builder.addCookie({.cookieName = "userId", .cookieValue = "pilnik2016@gmail.com"});

        auto request = builder.getResult();

        SocketSSL socket({"https://account.xiaomi.com"});
        std::cout << "Connect: " << socket.connect() << std::endl;
        std::cout << "Send: " << socket.send(request.c_str(),request.size()) << std::endl;
        std::string buf;
        std::cout << "Recv: " << socket.recv(buf) << std::endl;
        std::cout << buf;
    }

    std::string generateDeviceId() {
        constexpr int DEVICE_ID_LENGTH = 6;
        constexpr int ASCII_BEGIN = 97;
        constexpr int ASCII_END = 122;

        return generateRandomSequence(ASCII_BEGIN, ASCII_END, DEVICE_ID_LENGTH);
    }
    std::string generateAgent() {
        constexpr int AGENT_ID_LENGTH = 13;
        constexpr int ASCII_BEGIN = 65;
        constexpr int ASCII_END = 69;

        auto agentId = generateRandomSequence(ASCII_BEGIN, ASCII_END, AGENT_ID_LENGTH);

        return "Android-7.1.1-1.0.0-ONEPLUS A3010-136-" + agentId +" APP/xiaomi.smarthome APPV/62830";
    }

    static std::string generateRandomSequence(int begin, int end, int length) {
        std::string randomSequence;
        int distance = end - begin;

        unsigned int seed = time(NULL);
        srand(seed);

        for(int i = 0; i < length; ++i) {
            randomSequence += char(rand() % (distance+1) + begin);
        }
        return randomSequence;
    }

private:
    std::string m_login;
    std::string m_password;
    std::string m_agent;
    std::string m_deviceId;
    HttpRequestBuilder m_requestBuilder;
};

int main() {

    std::string login = "pilnik2016@gmail.com";
    std::string password = "egormerser39";

    auto connector = XiaomiCloudConnector(login, password);
    connector.login();
    return 0;
}