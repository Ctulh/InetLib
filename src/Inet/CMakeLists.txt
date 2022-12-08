set(LIB_NAME InetLib)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/Inet)

set(HEADERS ${INCLUDE_DIR}/InetAddress.hpp
            ${INCLUDE_DIR}/Socket.hpp
            ${INCLUDE_DIR}/TcpServer.hpp
            ${INCLUDE_DIR}/TcpConnection.hpp
            ${INCLUDE_DIR}/ConnectionAcceptor.hpp
            ${INCLUDE_DIR}/callbacks.hpp
            ${INCLUDE_DIR}/SocketPoller.hpp)

set(SOURCES InetAddress.cpp
            Socket.cpp
            TcpConnection.cpp
            ConnectionAcceptor.cpp
            SocketPoller.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIR}
                                              ${PROJECT_SOURCE_DIR}/include)
