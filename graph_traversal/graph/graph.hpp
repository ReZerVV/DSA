#ifndef GRAPH_H_
#define GRAPH_H_

#include <stddef.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

#define NONE 0
class graph {
public:
    graph(const size_t cv) {
        _adjacency_matrix.resize(cv);
        for (auto it = _adjacency_matrix.begin(); it != _adjacency_matrix.end(); ++it) {
            it->resize(cv);
        }
    }
    graph(const std::vector<std::vector<int32_t> > &adjacency_matrix)
        :
        _adjacency_matrix(adjacency_matrix) {}
    graph(const graph &other) 
        :
        _adjacency_matrix(other._adjacency_matrix) {}
    graph& operator=(const graph &other) {
        _adjacency_matrix = other._adjacency_matrix;
        return *this;
    }
    graph(graph &&other)
        :
        _adjacency_matrix(std::move(other._adjacency_matrix)) {}
    ~graph() {}
public:
    void append_edge(const int32_t fv, const int32_t sv, const int32_t weight) {
        _adjacency_matrix[fv][sv] = weight;
    }

    void remove_edge(const int32_t fv, const int32_t sv) {
        _adjacency_matrix[fv][sv] = NONE;
    }

    std::vector<int32_t> bfs(const int32_t start, const int32_t target = -1) {
        std::vector<int32_t> _spanning_tree{  };

        std::vector<bool> visited( _adjacency_matrix.size(), false );
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
            
            for (size_t u = 0; u < _adjacency_matrix[vertex].size(); ++u) {
                if (_adjacency_matrix[vertex][u] != NONE && !visited[u]) {
                    visited[u] = true;
                    vertices.push(u);
                }
            }
        }

        return _spanning_tree;
    }
    
    std::vector<std::pair<int32_t, int32_t> > dfs(const int32_t start, const int32_t target = -1) {
        std::vector<std::pair<int32_t, int32_t> > _spanning_tree{  };

        std::vector<bool> visited( _adjacency_matrix.size(), false );
        visited[start] = true;

        std::stack<int32_t> vertices{{ start }};

        while (!vertices.empty()) {
            int32_t vertex = vertices.top();
            vertices.pop();
            visited[vertex] = true;

            if (vertex == target) {
                break;
            }
            
            for (size_t u = 0; u < _adjacency_matrix[vertex].size(); ++u) {
                if (_adjacency_matrix[vertex][u] != NONE && !visited[u]) {
                    _spanning_tree.push_back({vertex, u});
                    vertices.push(u);
                    break;
                }
            }
        }

        return _spanning_tree;
    }
    
    friend std::ostream& operator<<(std::ostream &stream, const graph &g) {
        for (auto adjacency = g._adjacency_matrix.begin(); adjacency != g._adjacency_matrix.end(); ++adjacency) {
            for (auto it = adjacency->begin(); it != adjacency->end(); ++it) {
                stream << *it << "  ";
            }
            stream << std::endl;
        }
        return stream;
    }
public:
    std::vector<std::vector<int32_t> >  _adjacency_matrix;
};

#endif