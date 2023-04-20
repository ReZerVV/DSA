cmake_minimum_required(VERSION 3.0)
project(doubly_linked_list CXX)

include_directories(${PROJECT_NAME}
    include/
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/doubly_linked_list.cpp
)