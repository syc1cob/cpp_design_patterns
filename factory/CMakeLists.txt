cmake_minimum_required(VERSION 3.16)

project(FactoryPattern LANGUAGES CXX)

add_executable(factory
    src/main.cpp
    src/transport_factory.cpp
)

target_include_directories(factory
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(factory PRIVATE cxx_std_17)