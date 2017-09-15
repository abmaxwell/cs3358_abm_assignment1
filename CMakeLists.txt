cmake_minimum_required(VERSION 3.8)
project(cs3358_abm_assignment1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Assign01.cpp
        IntSet.cpp
        IntSet.h
        )

add_executable(cs3358_abm_assignment1 ${SOURCE_FILES})