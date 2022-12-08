# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.23)

# 프로젝트 정보
project(
        my_cpp
        VERSION 0.1
        DESCRIPTION "예제 프로젝트"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

# 라이브러리 파일은 빌드 디렉토리 안에 lib 폴더에 출력.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 실행 파일은 빌드 디렉토리 안에 bin 폴더에 출력.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)


################################################################################
# logsloth
add_subdirectory(third_party/logsloth)


################################################################################
# gtest
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)


################################################################################
# my_cpp
add_executable(
        my_cpp
        src/main.cpp
)

target_link_libraries(
        my_cpp
        gtest
        gmock
        gtest_main
        logsloth
)


################################################################################
# my_test
add_executable(
        my_test
        src/my_test.cpp
)

target_link_libraries(
        my_test
        gtest
        gmock
        gtest_main
        logsloth
)


################################################################################
# pg_000_food_fighter
add_executable(
        pg_000_food_fighter
        src/pg_000_food_fighter.cpp
)

target_link_libraries(
        pg_000_food_fighter
        gtest
        gmock
        gtest_main
        logsloth
)