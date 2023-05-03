/*
    У заданому графі пронумерувати вершини у відповідності з
    порядком обходу в глибину, визначити кількість ребер даного графа
    та кількість його вершин. Обчислити середню щільність графа у
    вигляді частки від ділення кількості ребер графа на кількість його
    вершин.
*/

#include <iostream>
#include "graph.hpp"
#include <vector>

void dfs(const graph &graph, std::vector<int32_t> &vertices, const int32_t start = 0) {
    std::vector<bool> visitor( graph._adjacency_matrix.size(), false );
    visitor[start] = true;
    
    std::stack<int32_t> stack_vertices{  };
    stack_vertices.push(start);
    
    size_t vertex_counter = 0;
    while (!stack_vertices.empty()) {
        
        int32_t vertex = stack_vertices.top();
        stack_vertices.pop();
        
        visitor[vertex] = true;

        vertices[vertex] = vertex_counter;
        vertex_counter += 1;
        
        for (size_t u = 0; u < graph._adjacency_matrix[vertex].size(); ++u) {
            if (graph._adjacency_matrix[vertex][u] != NONE && !visitor[u]) {
                stack_vertices.push(u);
            }
        }
    }
}

int main(int argc, char** argv) {
    graph g{ 4 };
    g.append_edge(0,3,1);
    g.append_edge(0,1,1);
    g.append_edge(1,0,1);
    g.append_edge(1,2,1);
    g.append_edge(2,1,1);
    g.append_edge(3,2,1);
    std::cout << g << std::endl;

    std::vector<int32_t> vs{ 0, 0, 0, 0};
    
    dfs(g, vs);

    for (size_t i = 0; i < vs.size(); ++i) {
        std::cout << i << "(" << vs[i] << ") ";
    }
    std::cout << std::endl;

    return 0;
}