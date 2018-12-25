cmake_minimum_required(VERSION 2.8)

project(virustotalcpp)

set(SOURCES
    src/main.cpp
    src/hasher.cpp
    src/include/hasher.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto")

add_executable(${PROJECT_NAME} ${SOURCES})
