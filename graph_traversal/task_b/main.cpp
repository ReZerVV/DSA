/*
    У заданому графі пронумерувати вершини у відповідності з
    порядком обходу в глибину, визначити кількість ребер даного графа
    та кількість його вершин. Обчислити середню щільність графа у
    вигляді частки від ділення кількості ребер графа на кількість його
    вершин.
*/

#include <iostream>
#include <iomanip>
#include "graph.hpp"
#include <vector>
#include <limits>

void dfs(const graph &graph, const int32_t start = 0) {
    std::vector<bool> visitor( graph._adjacency_matrix.size(), false );
    
    std::stack<int32_t> stack_vertices{  };
    stack_vertices.push(start);
    
    std::vector<int32_t> vertices( graph._adjacency_matrix.size(), std::numeric_limits<int32_t>::max() );
    size_t step_counter = 0;
    size_t edge_counter = 0;

    while (!stack_vertices.empty()) {

        int32_t vertex = stack_vertices.top();
        stack_vertices.pop();
        if (visitor[vertex]) {
            continue;
        }
        visitor[vertex] = true;
        
        step_counter += 1;
        vertices[vertex] = step_counter;


        for (size_t u = 0; u < graph._adjacency_matrix[vertex].size(); ++u) {
            if (graph._adjacency_matrix[vertex][u] != NONE && !visitor[u]) {
                stack_vertices.push(u);
                edge_counter += 1;
            }
        }
    }

    double graph_density = (edge_counter * 2.0d) / (graph._adjacency_matrix.size() * (graph._adjacency_matrix.size() - 1.0d));

    std::cout << "INFO:" << std::endl;
    std::cout << "\tvertex: " << graph._adjacency_matrix.size() << std::endl;
    std::cout << "\tedge: " << edge_counter << std::endl;
    std::cout << "graphic density: " << std::fixed << graph_density << std::endl;

    std::cout << "\tvertices: " << std::endl;
    for (size_t i = 0; i < vertices.size(); ++i) {
        std::cout << i << "("<< vertices[i] << ") "; 
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    graph g{ 4 };
    
    g.append_edge(0,1,1);
    g.append_edge(0,3,1);

    g.append_edge(1,0,1);
    g.append_edge(1,2,1);

    g.append_edge(2,1,1);
    g.append_edge(2,3,1);

    g.append_edge(3,2,1);
    g.append_edge(3,0,1);

    std::cout << g << std::endl;
    
    dfs(g);
    return 0;
}