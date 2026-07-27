cmake_minimum_required(VERSION 3.16)

project(StrategyPattern)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)

add_executable(strategy_pattern

    src/main.cpp
    src/payment_processor.cpp
)
