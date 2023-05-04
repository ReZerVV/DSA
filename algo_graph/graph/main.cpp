#include <iostream>
#include <iomanip>
#include "graph.hpp"
#include "algo.hpp"

int main(int argc, char **argv) {
    graph g{{ // INF == not path.
        {  0,  2,INF,INF,INF},
        {INF,  0,  2,  1,INF},
        {INF,INF,  0, -4,INF},
        {INF,  1,INF,  0,  3},
        {INF,INF,INF,INF,  0},
    }};
    std::cout << g << std::endl;
    
    std::cout <<  std::boolalpha << g.is_contains_negative_cycle() << std::endl;
    
    std::vector<int32_t> result = g.bellman_fords();
    { // print array.s
        std::cout << "result:" << std::endl;
        for (int32_t i = 0; i < result.size(); ++i) {
            if (result[i] == INF)
                std::cout << std::setw(5) << "inf";
            else
                std::cout << std::setw(5) << result[i];
        }
        std::cout << std::endl;
    }
    return 0;
}