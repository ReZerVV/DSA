cmake_minimum_required(VERSION 3.0)
project(b_tree CXX)
set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_NAME}
    include/
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)