cmake_minimum_required(VERSION 3.21)
project(CPPHM_lesson_8)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-main)
include_directories(lib/googletest-main/googletest/include)
include_directories(lib/googletest-main/googlemock/include)

add_executable(CPPHM_lesson_8 main.cpp Tests/tests.cpp Tests/ClassTests.h Tests/ClassTest.cpp)
target_link_libraries(CPPHM_lesson_8 gtest gtest_main)
