set(LIB_NAME SocketReaderLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/SocketReader)

set(HEADER ${INCLUDE_PATH}/SocketReader.hpp)
set(SOURCE SocketReader.cpp)

add_library(${LIB_NAME} ${HEADER} ${SOURCE})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH})