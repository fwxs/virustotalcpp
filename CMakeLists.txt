cmake_minimum_required(VERSION 2.8)

project(virustotalcpp)

set(SOURCES
    src/main.cpp
    src/hasher.cpp
    src/requester.cpp
    src/parser.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto -lcurl -ljsoncpp")

add_executable(${PROJECT_NAME} ${SOURCES})
