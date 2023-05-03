cmake_minimum_required(VERSION 3.0)
project(task CXX)

include_directories(${PROJECT_NAME}
    /home/cyril/Studies/dsa_c++/graph_traversal/graph
)

add_executable(${PROJECT_NAME}
    main.cpp
)