/*
    На мапі, представленій у вигляді графа, визначені аеропорти
    Європи. Для кожного існуючого перельоту між аеропортами
    визначено його вартість, при цьому вартість перельоту з аеропорту А
    в аеропорт В може не дорівнювати вартості перельоту з аеропорту В у
    аеропорт А. Визначити маршрут мінімальної вартості з Києва до
    Стокгольма, розглядаючи як прямі авіарейси, так і з пересадками.
*/

#include <iostream>
#include <iomanip>
#include "graph.hpp"
#include <vector>
#include <string>

const std::vector<std::string> capitals{
    "Kiev",
    "London",
    "Berlin",
    "Stockholm",
    "Dublin",
    "Warshaw",
    "Paris",
    "Monaco",
    "Oslo",
};

int main(int argc, char **argv) {
    graph g({
        { 0, 4, INF, INF, INF, INF, INF, 8, INF },
        { 4, 0, 8, INF, INF, INF, INF, 11, INF },
        { INF, 8, 0, 7, INF, 4, INF, INF, 2 },
        { INF, INF, 7, 0, 9, 14, INF, INF, INF },
        { INF, INF, INF, 9, 0, 10, INF, INF, INF },
        { INF, INF, 4, INF, 10, 0, 2, INF, INF },
        { INF, INF, INF, 14, INF, 2, 0, 1, 6 },
        { 8, 11, INF, INF, INF, INF, 1, 0, 7 },
        { INF, INF, 2, INF, INF, INF, 6, 7, 0 }
    });

    { // print graph
        std::cout << g << std::endl;
    }
    
    auto [distance, path] = g.dijkstra(0);
    
    std::vector<int32_t> path_to_stockholm{  };
    {
        path_to_stockholm.push_back(3);
        for (int32_t v = path[3]; v != INF; v = path[v]) {
            path_to_stockholm.push_back(v);
        }
        std::reverse(path_to_stockholm.begin(),  path_to_stockholm.end());
    }

    { // pring path ot stockholm
        for (auto it = path_to_stockholm.begin(); it != path_to_stockholm.end(); ++it) {
            std::cout << capitals[*it] << " -(" << distance[*it] << ")-> ";
        }
        std::cout << std::endl;
    }
    return 0;
}