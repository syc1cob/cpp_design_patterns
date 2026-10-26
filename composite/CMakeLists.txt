cmake_minimum_required(VERSION 3.16)

project(CompositePattern LANGUAGES CXX)

add_executable(composite
    src/main.cpp
    src/output_adapter.cpp
)

target_include_directories(composite
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(composite PRIVATE cxx_std_17)
