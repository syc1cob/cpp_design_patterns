cmake_minimum_required(VERSION 3.16)

project(PimplIdiom)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

add_executable(
    pimpl_demo
    src/main.cpp
    src/widget.cpp
)
