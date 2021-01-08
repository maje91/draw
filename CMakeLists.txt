cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

add_subdirectory(colex EXCLUDE_FROM_ALL)

project(draw)

set(LIB_NAME ${PROJECT_NAME})
set(TESTS_NAME ${PROJECT_NAME}_tests)

set(INC line.hpp)
set(SRC line.cpp)
set(TEST_SRC doctest.cpp doctest.hpp)

find_package(Eigen3 REQUIRED)

include_directories(SYSTEM /usr/local/include colex)
link_directories(/usr/local/lib)

add_library(${LIB_NAME} SHARED ${INC} ${SRC})
target_link_libraries(${LIB_NAME} Eigen3::Eigen colex)

add_executable(${TESTS_NAME} ${INC} ${SRC} ${TEST_SRC})
target_link_libraries(${TESTS_NAME} Eigen3::Eigen colex)