cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project (FlappyDuck CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(FlappyDuck main.cpp
        duck.h
        pipe.h
        collision.h
        settings.h
        particle.h)
target_link_libraries(FlappyDuck ${SDL2_LIBRARIES})
file(COPY ${CMAKE_SOURCE_DIR}/textures/ DESTINATION ${CMAKE_BINARY_DIR}/textures/)