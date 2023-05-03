/*
    Визначити порядок, за яким мають бути прочитані
    дисципліни під час навчання однієї з академічних груп. Моделювання
    виконати за допомогою графа, вершини якого представляють
    дисципліни, а орієнтовані ребра позначають вимоги до дисциплін
    (наприклад, курс C має бути прочитаний перед курсами A і B, а курс
    D – після курсу А тощо).
*/

#include <iostream>
#include "graph.hpp"
#include <vector>

std::vector<int32_t> bfs(const graph &graph, const int32_t start, const int32_t target) {
    std::queue<int32_t> vertices;
    std::vector<int32_t> indegrees( graph._adjacency_matrix.size(), 0);
    for (size_t i = 0; i < graph._adjacency_matrix.size(); ++i) {
        for (size_t j = 0; j < graph._adjacency_matrix.size(); ++j) {
            if (graph._adjacency_matrix[i][j] != NONE) {
                indegrees[j] += 1;
            }
        }
    }

    for (size_t v = 0; v < indegrees.size(); ++v) {
        if (indegrees[v] == 0) {
            vertices.push(v);
        }
    }

    std::vector<int32_t> result{  };
    while (!vertices.empty()) {
        int32_t vertex = vertices.front();
        vertices.pop();
        
        result.push(vertex);

        for (size_t u = 0; u < graph._adjacency_matrix.size(); ++u) {
            if (graph._adjacency_matrix[vertex][u] != NONE) {
                indegrees[u] -= 1;
                if (indegrees[u] == 0) {
                    vertices.push(u);
                }
            }
        }
    }

    return result;
}

int main(int argc, char** argv) {
    graph g{{
        {0,0,1,1},
        {0,0,1,0},
        {0,0,0,0},
        {0,0,0,0},
    }};
    std::cout << g << std::endl;

    bfs(g, 0, 2);
    return 0;
}