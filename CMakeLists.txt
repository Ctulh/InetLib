cmake_minimum_required(VERSION 3.23)
project(InetLib)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

add_executable(Main main.cpp)

target_link_libraries(Main InetLib SocketReaderLib HttpLib UtilsLib)

target_include_directories(Main PUBLIC include)