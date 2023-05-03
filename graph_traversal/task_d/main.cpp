/*
    Неорієнтований граф, у кожній вершині якого зберігаються
    натуральні числа, задано користувачем. Визначити, скільки в даному
    графі є пар взаємно простих чисел (тобто чисел, які не мають ніяких
    спільних дільників крім одиниці), розташованих у вершинах графа,
    що з’єднані ребрами.
*/

#include <iostream>
#include <vector>
#include "graph.hpp"

int32_t gcd(int32_t fnum, int32_t snum) {
    while (fnum != 0 && snum != 0) {
        if (fnum > snum) {
            fnum = fnum % snum;
        }
        else snum = snum % fnum;
    }
    return fnum + snum;
}

int32_t gcd_pair_from_graph(const graph &graph, const std::vector<int32_t> values, const int32_t start = 0) {
    size_t gcd_pair_count = 0;

    std::vector<bool> visitor( graph._adjacency_matrix.size(), false );
    visitor[start] = true;
    
    std::stack<int32_t> vertices{  };
    vertices.push(start);
    
    while (!vertices.empty()) {
        int32_t vertex = vertices.top();
        vertices.pop();
        visitor[vertex] = true;
        
        for (size_t u = 0; u < graph._adjacency_matrix[vertex].size(); ++u) {
            if (graph._adjacency_matrix[vertex][u] != NONE) {
                if (gcd(values[vertex], values[u]) == 1) {
                    std::cout << "\t(" << values[vertex] << ")-(" << values[u] << ")" << std::endl;
                    gcd_pair_count += 1;
                }
                if (!visitor[u]) {
                    vertices.push(u);
                }
            }
        }
    }

    return gcd_pair_count;
}

int main(int argc, char** argv) {
    graph g{ 3 };
    g.append_edge(0,1,1);
    g.append_edge(1,0,1);
    g.append_edge(1,2,1);
    g.append_edge(2,1,1);
    std::cout << g << std::endl;

    std::vector<int32_t> values{ 10, 1, 8 };

    std::cout << gcd_pair_from_graph(g, values) << std::endl;
    return 0;
}