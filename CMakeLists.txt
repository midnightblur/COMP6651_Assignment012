cmake_minimum_required(VERSION 3.8)
project(COMP6651_Assignment02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NaiveAlgo.cpp NaiveAlgo.h SuffixTreeAlgo.h)
add_executable(COMP6651_Assignment02 ${SOURCE_FILES})