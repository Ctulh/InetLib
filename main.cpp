#include <iostream>

#include "include/Http/HttpBuilder.hpp"
#include "HttpRequestBuilder.hpp"
#include "Inet/TcpConnection.hpp"
#include "Inet/SocketSSL.hpp"
#include <cstring>
#include <fstream>
#include "HttpParser.hpp"
#include "Utils/JsonParser.hpp"

class XiaomiCloudConnector {
public:
    XiaomiCloudConnector(std::string login, std::string password) {
        m_login = login;
        m_password = password;

        m_agent = generateAgent();
        m_deviceId = generateDeviceId();
    }

    bool login() {

        //m_requestBuilder.addCookie({.cookieName= "sdkVersion", .cookieValue = "accountsdk-18.8.15", .cookieDomain = "mi.com"});
     //m_requestBuilder.addCookie({.cookieName= "sdkVersion", .cookieValue = "accountsdk-18.8.15", .cookieDomain = "xiaomi.com"});
        //m_requestBuilder.
     //   m_requestBuilder.addCookie({.cookieName= "deviceId", .cookieValue = m_deviceId, .cookieDomain = "xiaomi.com"});

        if(loginFirstStep()) {
            if(loginSecondStep()) {

            }
        }
    }

private:

    bool loginSecondStep() {

    }

    bool loginFirstStep() {
        HttpRequestBuilder builder;
        //builder.addCookie({.cookieName= "deviceId", .cookieValue = m_deviceId, .cookieDomain = "mi.com"});
       // builder.addCookie({.cookieName= "sdkVersion", .cookieValue = "accountsdk-18.8.15", .cookieDomain = "mi.com"});
        builder.setHttpMethod(HttpMethod::GET);
        builder.setUri("/pass/serviceLogin?sid=xiaomiio&_json=true");
        builder.setUserAgent(generateAgent());
        builder.setHost("account.xiaomi.com");
        builder.setContentType("application/x-www-form-urlencoded");

        builder.setAccept("*/*");
        builder.addCookie({.cookieName = "userId", .cookieValue = "pilnik2016@gmail.com"});

        auto request = builder.getResult();
        std::cout << request << std::endl;

        SocketSSL socket({"https://account.xiaomi.com"});
        std::cout << "Connect: " << socket.connect() << std::endl;
        std::cout << "Send: " << socket.send(request.c_str(),request.size()) << std::endl;
        std::string buf;
        std::cout << "Recv: " << socket.recv(buf) << std::endl;
        std::cout << buf;

        JsonParser jsonParser(buf);
        if(!jsonParser["_sign"].has_value()) {
            buf.clear();
            std::cout << "Recv: " << socket.recv(buf) << std::endl;
            std::cout << buf;
            JsonParser jsonParser2(buf);
            if(jsonParser2["_sign"].has_value()) {
                std::cout << jsonParser2["_sign"].value();
                m_sign = jsonParser2["_sign"].value();
                return true;
            }
        }
        else {
            std::cout << jsonParser["_sign"].value();
            m_sign = jsonParser["_sign"].value();
            return true;
        }
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
    std::string m_sign;
    HttpRequestBuilder m_requestBuilder;
};

int main() {

    std::string login = "pilnik2016@gmail.com";
    std::string password = "egormerser39";

    //JsonParser parser("&&&START&&&{\"serviceParam\":\"{\\\"checkSafePhone\\\":false,\\\"checkSafeAddress\\\":false,\\\"lsrp_score\\\":0.0}\",\"qs\":\"%3Fsid%3Dxiaomiio%26_json%3Dtrue\",\"code\":70016,\"description\":\"登录验证失败\",\"securityStatus\":0,\"_sign\":\"0psXfr43eNI0IX6q9Suk3qWbRqU=\",\"sid\":\"xiaomiio\",\"result\":\"error\",\"captchaUrl\":null,\"callback\":\"https://sts.api.io.mi.com/sts\",\"location\":\"https://account.xiaomi.com/fe/service/login?_json=true&sid=xiaomiio&qs=%253Fsid%253Dxiaomiio%2526_json%253Dtrue&callback=https%3A%2F%2Fsts.api.io.mi.com%2Fsts&_sign=0psXfr43eNI0IX6q9Suk3qWbRqU%3D&serviceParam=%7B%22checkSafePhone%22%3Afalse%2C%22checkSafeAddress%22%3Afalse%2C%22lsrp_score%22%3A0.0%7D&showActiveX=false&theme=&needTheme=false&bizDeviceType=\",\"pwd\":0,\"child\":0,\"desc\":\"登录验证失败\"}");
    //std::cout << parser["_sign"].value();

    auto connector = XiaomiCloudConnector(login, password);
    connector.login();
    return 0;
}