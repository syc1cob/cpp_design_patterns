cmake_minimum_required(VERSION 3.16)

project(ObserverPattern LANGUAGES CXX)

add_executable(observer
    src/main.cpp
    src/speed_source.cpp
)

target_include_directories(observer
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(observer PRIVATE cxx_std_17)