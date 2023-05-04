#include <iostream>
#include "graph.hpp"
#include "algo.hpp"

int main(int argc, char **argv) {
    graph g{{
        {0,7,9,0,0,14},
        {7,0,10,15,0,0},
        {9,10,0,11,0,2},
        {0,15,11,0,6,0},
        {0,0,0,6,0,9},
        {14,0,2,0,9,0},
    }};
    
    std::cout << g << std::endl;
    
    std::vector<int32_t> path = g.dijkstra();
    for (int32_t i = 0; i < path.size(); ++i) {
        std::cout << i << "(" << path[i] << ") ";
    }
    std::cout << std::endl;
    return 0;
}