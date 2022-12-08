# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.23)

# 프로젝트 정보
project(
        logsloth
        VERSION 0.1
        DESCRIPTION "logsloth"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_library(
        logsloth
        STATIC
        src/logsloth.cpp
)

target_include_directories(
        logsloth
        PUBLIC
        include
)