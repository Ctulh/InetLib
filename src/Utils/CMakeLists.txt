set(LIB_NAME UtilsLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/Utils)

set(HEADERS  ${INCLUDE_PATH}/JsonParser.hpp)

set(SOURCES JsonParser.cpp)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH})