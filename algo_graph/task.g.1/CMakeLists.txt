cmake_minimum_required(VERSION 3.0)
project(task CXX)
set (CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_NAME}
    /home/cyril/Studies/dsa_c++/algo_graph/graph/
)

add_executable(${PROJECT_NAME}
    main.cpp
)