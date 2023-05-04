#ifndef GRAPH_H_
#define GRAPH_H_

#include <stddef.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

#define NONE 0
// #define INF std::numeric_limits<int32_t>::max()
#define INF 9999

class graph {
public:
    struct edge {
        int32_t v; // start vertex.
        int32_t u; // end vertex;
        int32_t w; // weight vertex;
    };

    using edge_type = edge;

public:
    graph(const std::string file_path) {
        graph_from_file(file_path);
    } 
    graph(const size_t cv)
        :
        nodes( cv, std::vector<int32_t>(cv, INF)) {}
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
    void graph_from_file(const std::string file_path) {
        std::ifstream file;
        file.open(file_path);
        if (!file.is_open()) {
            std::cout << "file is not found: " << file_path << std::endl;
            return;
        }
        
        std::string line{  };

        try {
            getline(file, line);
            nodes = std::vector<std::vector<int32_t> >( std::stoi(line), std::vector<int32_t>(std::stoi(line)));
            for (int32_t i = 0; getline(file, line); ++i) {
                for (int32_t j = 0, pos = line.find(" "); line.find(" ") != std::string::npos; pos = line.find(" "), ++j) {
                    nodes[i][j] = std::stoi(line.substr(0, pos));
                    std::cout << std::stoi(line.substr(0, pos)) << "  "; 
                    line.erase(0, pos + 1);
                }
                std::cout << std::endl;
            }
        } catch (...) {
            nodes = std::vector<std::vector<int32_t> >( 1, std::vector<int32_t>(1, INF));
            std::cout << "incorrect data graph."  << std::endl;
        }
    }
    void graph_to_file(const std::string file_path) {
        std::ofstream file;
        file.open(file_path);
        if (!file.is_open()) {
            std::cout << "file is not found: " << file_path << std::endl;
            return;
        }
        file << nodes.size() << std::endl;
        for (int32_t i = 0; i < nodes.size(); ++i) {
            for (int32_t j = 0; j < nodes.size(); ++j) {
                file << nodes[i][j] << ' ';
            }
            file << std::endl;
        }
        file.close();
    }
    void append_edge(const int32_t fv, const int32_t sv, const int32_t weight) {
        nodes[fv][sv] = weight;
    }
    void remove_edge(const int32_t fv, const int32_t sv) {
        nodes[fv][sv] = INF;
    }
    bool is_contains_negative_cycle() {
        std::vector<int32_t> bellman_fords_result = bellman_fords();
        for (auto it = bellman_fords_result.begin(); it != bellman_fords_result.end(); ++it) {
            if (*it != INF) {
                return false;
            }
        }
        return true;
    }
    std::vector<int32_t> get_negative_cycle(const int32_t start = 0) {
        std::vector<int32_t> path( nodes.size(), -1 );
        std::vector<int32_t> distance( nodes.size(), INF );
        std::vector<edge_type> edges = edge_list_from_matrix(nodes);
        
        distance[start] = 0;
        for (int32_t i = 1; i <= nodes.size() - 1; ++i) {
            for (int32_t j = 0; j < edges.size(); ++j) {
                int32_t v = edges[j].v;
                int32_t u = edges[j].u;
                int32_t w = edges[j].w;
                if (distance[v] != INF && distance[v] + w < distance[u]) {
                    distance[u] = distance[v] + w;
                    path[u] = v;
                }
            }
        }

        int32_t cycle_index = -1;
        for (cycle_index = 0; cycle_index < edges.size(); ++cycle_index) {
            int32_t v = edges[cycle_index].v;
            int32_t u = edges[cycle_index].u;
            int32_t w = edges[cycle_index].w;
            if (distance[v] != INF && distance[v] + w < distance[u]) {
                break;
            }
        }
        if (cycle_index != -1) {
            for (int32_t i = 0; i < nodes.size(); ++i) {
                cycle_index = path[cycle_index];
            }
            
            std::vector<int32_t> cycle{ };
            for (int32_t v = cycle_index;; v = path[v]) {
                cycle.push_back(v);
                if (v == cycle_index && cycle.size() > 1) {
                    break;
                }
            }

            std::reverse(cycle.begin(), cycle.end());
            return cycle;
        }

        return std::vector<int32_t>{  };
    }
    static std::vector<edge_type> edge_list_from_matrix(const std::vector<std::vector<int32_t> > matrix) {
        std::vector<edge_type> edges{  };
        for (int32_t i = 0; i < matrix.size(); ++i) {
            for (int32_t j = 0; j < matrix.size(); ++j) {
                if (i != j && matrix[i][j] != INF) {
                    edges.push_back({ i, j, matrix[i][j] });
                }
            }
        } 
        return edges;
    }

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
                if (nodes[vertex][u] != INF && !visited[u]) {
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
                if (nodes[vertex][u] != INF && !visited[u]) {
                    _spanning_tree.push_back({vertex, u});
                    vertices.push(u);
                    break;
                }
            }
        }

        return _spanning_tree;
    }
    std::pair<std::vector<int32_t>, std::vector<int32_t> > dijkstra(const int32_t start = 0) {
        std::vector<int32_t> path( nodes.size(), INF );
        std::vector<int32_t> distance( nodes.size(), INF );
        std::vector<bool> visitor( nodes.size(), false );
        
        distance[start] = 0;
        {  
            for (int32_t vertex = 0; vertex < nodes.size(); ++vertex) {
                int32_t min_distance_index = -1;
                for (int32_t i = 0; i < distance.size(); ++i) {
                    if (!visitor[i] && (distance[i] < distance[min_distance_index] || min_distance_index == -1) ) {
                        min_distance_index = i;
                    }
                }
                
                if (min_distance_index == -1) continue;
                int32_t v = min_distance_index;
                visitor[v] = true;

                for (int32_t u = 0; u < nodes.size(); ++u) {
                    if (!visitor[u] && nodes[v][u] != INF && distance[v] + nodes[v][u] < distance[u]) {
                        distance[u] = distance[v] + nodes[v][u];
                        path[u] = v;
                    }
                    //distance[u] = std::min(distance[v] + nodes[v][u], distance[u]);
                }
            }
        }

        return std::make_pair(distance, path);
    }
    std::vector<std::vector<int32_t> > floyd_warshall() {
        std::vector<std::vector<int32_t> > distance = nodes;

        for (int32_t k = 0; k < nodes.size(); ++k) {
            for (int32_t i = 0; i < nodes.size(); ++i) {
                for (int32_t j = 0; j < nodes.size(); ++j) {
                    distance[i][j] = std::min(distance[i][j], distance[i][k] + distance[k][j]);
                }
            }
        }

        return distance;
    }
    std::vector<int32_t> bellman_fords(const int32_t start = 0) {
        std::vector<edge_type> edges = edge_list_from_matrix(nodes);

        std::vector<int32_t> distance( nodes.size(), INF );
        distance[start] = 0;

        for (int32_t i = 1; i <= nodes.size() - 1; ++i) {
            for (int32_t j = 0; j < edges.size(); ++j) {
                int32_t v = edges[j].v;
                int32_t u = edges[j].u;
                int32_t w = edges[j].w;
                if (distance[v] != INF && distance[v] + w < distance[u]) {
                    distance[u] = distance[v] + w;                    
                }
            }
        }

        for (int32_t i = 0; i < edges.size(); ++i) {
            int32_t v = edges[i].v;
            int32_t u = edges[i].u;
            int32_t w = edges[i].w;
            if (distance[v] != INF && distance[v] + w < distance[u]) {
                return std::vector<int32_t>( nodes.size(), INF );
            }
        }

        return distance; 
    }

    friend std::ostream& operator<<(std::ostream &stream, const graph &g) {
        stream << "graph:" << std::endl;
        for (auto adjacency = g.nodes.begin(); adjacency != g.nodes.end(); ++adjacency) {
            for (auto it = adjacency->begin(); it != adjacency->end(); ++it) {
                if (*it == INF) {
                    stream << std::setw(5) << "inf";
                    continue;
                }
                stream << std::setw(5) << *it;
            }
            stream << std::endl;
        }
        return stream;
    }
public:
    std::vector<std::vector<int32_t> >  nodes;
};

#endif