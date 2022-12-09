cmake_minimum_required(VERSION 3.23)
project(InetLib)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

add_executable(InetLibTest main.cpp)

target_link_libraries(InetLibTest PRIVATE InetLib HttpLib SocketReaderLib)
