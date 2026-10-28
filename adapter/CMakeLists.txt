cmake_minimum_required(VERSION 3.16)

project(AdapterPattern LANGUAGES CXX)

add_executable(adapter
    src/main.cpp
    src/legacy_speed_sensor.cpp
    src/speed_sensor_adapter.cpp
)

include_directories(inc)

target_compile_features(adapter PRIVATE cxx_std_17)