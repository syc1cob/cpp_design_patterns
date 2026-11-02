cmake_minimum_required(VERSION 3.16)

project(StatePattern LANGUAGES CXX)

add_executable(state
    src/main.cpp
    src/diagnostic_connection.cpp
)

target_include_directories(state
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(state PRIVATE cxx_std_17)