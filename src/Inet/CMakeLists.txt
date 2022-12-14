set(LIB_NAME InetLib)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/Inet)

set(HEADERS ${INCLUDE_DIR}/InetAddress.hpp
            ${INCLUDE_DIR}/Socket.hpp
            ${INCLUDE_DIR}/TcpServer.hpp
            ${INCLUDE_DIR}/TcpConnection.hpp
            ${INCLUDE_DIR}/ConnectionAcceptor.hpp
            ${INCLUDE_DIR}/callbacks.hpp
            ${INCLUDE_DIR}/SocketPoller.hpp
            ${INCLUDE_DIR}/Strategy.hpp)


set(SOURCES InetAddress.cpp
            Socket.cpp
            SocketSSL.cpp
            TcpConnection.cpp
            ConnectionAcceptor.cpp
            SocketPoller.cpp
        )


add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIR}
                                              ${PROJECT_SOURCE_DIR}/include
                                                /usr/local/ssl/include
                                                )



target_link_libraries(${LIB_NAME} PRIVATE "/usr/lib64/libssl.so" "/usr/lib64/libcrypto.so")
