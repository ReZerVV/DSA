#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "hash_table.hpp"

struct hash {
    size_t operator()(const std::string &str) {
        size_t hash_value = 0; 
        for (auto it = str.begin(); it != str.end(); ++it) {
            hash_value += static_cast<size_t>(*it);
        }
        return hash_value * 20 % 100;
    }
};

struct step_hash {
    size_t operator()(const std::string &str) {
        size_t hash_value = 0; 
        for (auto it = str.begin(); it != str.end(); ++it) {
            hash_value += static_cast<size_t>(*it);
        } 
        return (hash_value * 5 / 3) * 10;
    }
};

std::vector<std::string> split(const std::string& str, const std::string& sep) {
    std::vector<std::string> result{  };

    size_t i = 0, j = 0;
    while ( i + sep.size() < str.size() ) {
        if ( str[i] == sep[0] && str.substr( i, sep.size() ) == sep ) {
            result.push_back( str.substr( j, i - j ) );
            i = j = i + sep.size();
        } else {
            i++;
        }
    }
    result.push_back( str.substr( j, str.size() - j ) );

    return result;
}

std::vector<std::pair<std::string, std::string> > corporation_from_file(const char* file_path) {
    std::ifstream file;
    file.open(file_path);
    if (!file.is_open()) {
        std::cout << "File is not open: " << file_path << std::endl;
        return std::vector<std::pair<std::string, std::string> >{  };
    }
    std::vector<std::pair<std::string, std::string> > data{  };
    std::string line{  };
    while (getline(file, line)) {
        std::vector<std::string> res = split( line, std::string{ " " } );
        if (res.size() < 2) {
            continue;
        }
        data.push_back(make_pair(res[0], res[1]));
    }
    file.close();
    return data;
}

int main(int argc, char** argv) {
    
    std::vector<std::pair<std::string, std::string> > data = corporation_from_file("/home/cyril/Programming/dsa_c++/trees_and_hash_table/task_d/data.txt");
    hash_table<std::string, std::string, hash, step_hash> ht{  };
    for (auto it = data.begin(); it != data.end(); ++it) {
        ht.append(it->second, it->first);
    }
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << it->second << " : " << ht[it->second] << std::endl;
    }
    return 0;
}