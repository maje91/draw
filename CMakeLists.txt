cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

add_subdirectory(colex EXCLUDE_FROM_ALL)

project(draw)

set(LIB_NAME ${PROJECT_NAME})
set(TESTS_NAME ${PROJECT_NAME}_tests)
set(MAIN_NAME ${PROJECT_NAME}_main)

set(INC line.hpp window.hpp shader.hpp render.hpp transformation.hpp)
set(SRC line.cpp window.cpp shader.cpp render.cpp transformation.cpp)
set(TEST_SRC doctest.cpp doctest.hpp)
set(MAIN_SRC main.cpp)
set(GLAD_SRC glad/src/glad.c)

find_package(Eigen3 REQUIRED)

include_directories(SYSTEM /usr/local/include colex glad/include)
link_directories(/usr/local/lib)

add_library(${LIB_NAME} SHARED ${INC} ${SRC} ${GLAD_SRC})
target_link_libraries(${LIB_NAME} Eigen3::Eigen colex glfw GL X11 pthread Xrandr Xi dl)

add_executable(${TESTS_NAME} ${INC} ${SRC} ${TEST_SRC} ${GLAD_SRC})
target_link_libraries(${TESTS_NAME} Eigen3::Eigen colex glfw GL X11 pthread Xrandr Xi dl)

add_executable(${MAIN_NAME} ${INC} ${SRC} ${MAIN_SRC} ${GLAD_SRC})
target_link_libraries(${MAIN_NAME} Eigen3::Eigen colex glfw GL X11 pthread Xrandr Xi dl)
