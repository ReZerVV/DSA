#ifndef GRAPH_H_
#define GRAPH_H_

#include <stddef.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <limits>

#define NONE 0
class graph {
public:
    graph(const size_t cv) {
        nodes.resize(cv);
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            it->resize(cv);
        }
    }
    graph(const std::vector<std::vector<int32_t> > &adjacency_matrix)
        :
        nodes(adjacency_matrix) {}
    graph(const graph &other) 
        :
        nodes(other.nodes) {}
    graph& operator=(const graph &other) {
        nodes = other.nodes;
        return *this;
    }
    graph(graph &&other)
        :
        nodes(std::move(other.nodes)) {}
    ~graph() {}
public:
//
    void append_edge(const int32_t fv, const int32_t sv, const int32_t weight) {
        nodes[fv][sv] = weight;
    }

    void remove_edge(const int32_t fv, const int32_t sv) {
        nodes[fv][sv] = NONE;
    }
// 
    std::vector<int32_t> bfs(const int32_t start, const int32_t target = -1) {
        std::vector<int32_t> _spanning_tree{  };

        std::vector<bool> visited( nodes.size(), false );
        visited[start] = true;
        
        std::queue<int32_t> vertices;
        vertices.push(start);

        while (!vertices.empty()) {
            int32_t vertex = vertices.front();
            vertices.pop();
            _spanning_tree.push_back(vertex);

            if (vertex == target) {
                break;
            }
            
            for (size_t u = 0; u < nodes[vertex].size(); ++u) {
                if (nodes[vertex][u] != NONE && !visited[u]) {
                    visited[u] = true;
                    vertices.push(u);
                }
            }
        }

        return _spanning_tree;
    }
    
    std::vector<std::pair<int32_t, int32_t> > dfs(const int32_t start, const int32_t target = -1) {
        std::vector<std::pair<int32_t, int32_t> > _spanning_tree{  };

        std::vector<bool> visited( nodes.size(), false );
        visited[start] = true;

        std::stack<int32_t> vertices{  };
        vertices.push(start);

        while (!vertices.empty()) {
            int32_t vertex = vertices.top();
            vertices.pop();
            visited[vertex] = true;

            if (vertex == target) {
                break;
            }
            
            for (size_t u = 0; u < nodes[vertex].size(); ++u) {
                if (nodes[vertex][u] != NONE && !visited[u]) {
                    _spanning_tree.push_back({vertex, u});
                    vertices.push(u);
                    break;
                }
            }
        }

        return _spanning_tree;
    }
//
    std::vector<int32_t> dijkstra(const int32_t start = 0) {
        std::vector<int32_t> distance( nodes.size(), std::numeric_limits<int32_t>::max() );
        distance[start] = 0;

        std::vector<bool> visitor( nodes.size(), false );

        std::stack<int32_t> vertices{  };
        vertices.push(start);

        while (!vertices.empty()) {
            int32_t vertex = vertices.top();
            vertices.pop();
            if (visitor[vertex]) {
                continue;
            }
            visitor[vertex] = true;

            int32_t min_edge_vertex_index = -1;
            for (int32_t u = 0; u < nodes[vertex].size(); ++u) {
                if (nodes[vertex][u] != NONE && !visitor[u]) {
                    distance[u] = std::min(distance[vertex] + nodes[vertex][u], distance[u]);

                    if (min_edge_vertex_index == -1 || distance[u] < distance[min_edge_vertex_index]) {
                        min_edge_vertex_index = u;
                    }
                }
            }
            
            if (min_edge_vertex_index != -1) {
                vertices.push(min_edge_vertex_index);
            }
        }

        return distance;
    }
//  
    friend std::ostream& operator<<(std::ostream &stream, const graph &g) {
        for (auto adjacency = g.nodes.begin(); adjacency != g.nodes.end(); ++adjacency) {
            for (auto it = adjacency->begin(); it != adjacency->end(); ++it) {
                stream << *it << "  ";
            }
            stream << std::endl;
        }
        return stream;
    }
public:
    std::vector<std::vector<int32_t> >  nodes;
};

#endif