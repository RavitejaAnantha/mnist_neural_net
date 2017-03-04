cmake_minimum_required(VERSION 3.6)
project(NN_C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp utils/MathNN.cpp utils/MathNN.h)
add_executable(NN_C ${SOURCE_FILES})