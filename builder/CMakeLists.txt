cmake_minimum_required(VERSION 3.16)

project(BuilderPattern LANGUAGES CXX)

add_executable(builder
    src/main.cpp
    src/someip_config.cpp
)

target_include_directories(builder
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc 
)

target_compile_features(builder PRIVATE cxx_std_17)