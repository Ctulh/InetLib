set(LIB_NAME HttpLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/Http)

set(HEADERS ${INCLUDE_PATH}/HttpResponseBuilder.hpp
            ${INCLUDE_PATH}/HttpRequestBuilder.hpp
            ${INCLUDE_PATH}/HttpVersion.hpp
            ${INCLUDE_PATH}/HttpMessage.hpp
            ${INCLUDE_PATH}/HttpParser.hpp)

set(SOURCES HttpResponseBuilder.cpp
            HttpRequestBuilder.cpp
            HttpBuilder.cpp
            HttpMethod.cpp
            HttpParser.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH})