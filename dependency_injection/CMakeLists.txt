cmake_minimum_required(VERSION 3.16)

project(DependencyInjection LANGUAGES CXX)

add_executable(dependency_injection
    src/main.cpp
    src/console_logger.cpp
    src/diagnostic_manager.cpp
)

target_include_directories(dependency_injection
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(
    dependency_injection PRIVATE cxx_std_17
)