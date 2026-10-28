cmake_minimum_required(VERSION 3.16)

project(AbstractFactoryPattern LANGUAGES CXX)

add_executable(abstract_factory
    src/main.cpp
    src/linux_platform.cpp
    src/qnx_platform.cpp
)

target_include_directories(abstract_factory
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(abstract_factory PRIVATE cxx_std_17)