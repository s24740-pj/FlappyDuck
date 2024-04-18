cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project (FlappyDuck CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
#include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(FlappyDuck main.cpp)
target_link_libraries(FlappyDuck ${SDL2_LIBRARIES})