cmake_minimum_required(VERSION 3.21)
project(ArduPi)

set(CMAKE_CXX_STANDARD 14)

add_executable(Main src/MainSnake.cpp src/SnakeLib.h)
add_executable(Main2 src/newFile.cpp)