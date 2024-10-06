cmake_minimum_required(VERSION 3.27)
project(DIAN_PRO_CPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(DIAN_PRO_CPP src/main.cpp
        src/setup.hpp
        src/buffer.cpp
        src/cell.cpp
        src/setup.cpp
        src/display.cpp
        src/sevsegdisp.cpp
        src/field.cpp)
