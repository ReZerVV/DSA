cmake_minimum_required(VERSION 3.0)
project(weather CXX)

include_directories(${PROJECT_NAME}
    include/
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)