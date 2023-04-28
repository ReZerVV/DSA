#include <stddef.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "b_tree.hpp"

enum machine_type : uint8_t {
    MT_1 = 0,
    MT_2,
    MT_3,
};

std::string machine_type_to_string(const machine_type type) {
    switch (type) {
    case machine_type::MT_1: return "MT_1";
    case machine_type::MT_2: return "MT_2";
    case machine_type::MT_3: return "MT_3";
    default: return "NULL";
    }
}

class machine {
public:
    machine() {}
    machine(const size_t id, const std::string &name, const enum machine_type type, const size_t downtime, const size_t worktime)
        :
        id(id),
        name(name),
        type((machine_type)type),
        downtime(downtime),
        worktime(worktime) {}

    machine(const machine &other)
        :
        id(other.id),
        name(other.name),
        type(other.type),
        downtime(other.downtime),
        worktime(other.worktime) {}
    
    machine& operator=(const machine &other) {
        id = other.id;
        name = other.name;
        type = other.type;
        downtime = other.downtime;
        worktime = other.worktime;
        return *this;
    }
    
    ~machine() {}
public:
    bool operator<(const machine &other) {
        return other.id < other.id;
    }

    bool operator>(const machine &other) {
        return other.id > other.id;
    }

    friend std::ostream& operator<<(std::ostream &stream, const machine &machine) {
        stream << machine.id;
        return stream;
    }
public:
    size_t id;
    std::string name;
    machine_type type;
    size_t downtime;
    size_t worktime;
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

b_tree<machine> b_tree_from_file(const char* file_path) {
    std::ifstream file;
    file.open(file_path);
    if (!file.is_open()) {
        std::cout << "File is not open: " << file_path << std::endl;
        return b_tree<machine>{ 2 };
    }
    b_tree<machine> data{ 2 };
    std::string line{  };
    while (getline(file, line)) {
        std::vector<std::string> res = split(line, std::string{ " " });
        machine m{
            std::stoi(res[0]),
            res[1],
            static_cast<machine_type>(std::stoi(res[2])),
            std::stoi(res[3]),
            std::stoi(res[4])
        };
        data.append(m);
    }
    file.close();
    return std::move(data);
}

float get_worktime(node_b_tree<machine> *node) {
    float worktime = 0.0f;
    int index = 0;
    for (index = 0; index < node->size(); ++index) {
        if (!node->leaf()) {
            worktime += get_worktime(node->nodes()[index]);
        }
        worktime += node->keys()[index].worktime;
    }
    if (!node->leaf()) {
        worktime += get_worktime(node->nodes()[index]);
    }
    return worktime;
}

float get_worktime_by_machine_type(node_b_tree<machine> *node, machine_type type) {
    float worktime = 0.0f;
    int index = 0;
    for (index = 0; index < node->size(); ++index) {
        if (!node->leaf()) {
            worktime += get_worktime_by_machine_type(node->nodes()[index], type);
        }
        if (node->keys()[index].type == type) {
            worktime += node->keys()[index].worktime;
        }
    }
    if (!node->leaf()) {
        worktime += get_worktime_by_machine_type(node->nodes()[index], type);
    }
    return worktime;
}

machine_type get_machine_type_used(node_b_tree<machine> *node) {
    machine_type type_res = machine_type::MT_1;
    float type_res_worktime = 0;
    for (size_t type = 0; type < 3; ++type) {
        float type_worktime = get_worktime_by_machine_type(node, static_cast<machine_type>(type));
        if (type_res_worktime < type_worktime) {
            type_res_worktime = type_worktime;
            type_res = static_cast<machine_type>(type);
        }
    }
    return type_res;
}

bool isdigit(const std::string &str) {
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (!isdigit(*it)) {
            return false;
        }
    }
    return true;
}

machine* find_machine_by_id(node_b_tree<machine> *node, const size_t id) {
    int index = 0;
    for (index = 0; index < node->size(); ++index) {
        if (!node->leaf()) {
            machine *m = find_machine_by_id(node->nodes()[index], id);
            if (m != nullptr) {
                return m;
            }
        }
        if (node->keys()[index].id == id) {
            return &node->keys()[index];
        }
    }
    if (!node->leaf()) {
        machine *m = find_machine_by_id(node->nodes()[index], id);
        if (m != nullptr) {
            return m;
        }
    }
    return nullptr;
}

int main(int argc, char** argv) {
    b_tree<machine> data = b_tree_from_file("/home/cyril/Programming/dsa_c++/trees_and_hash_table/task_a/data.txt");
    std::cout << "The type of machine that was used the most: " << machine_type_to_string(get_machine_type_used(data.root())) << std::endl;
    
    std::string command{  };
    while (true) {
        std::cin >> command;
        if (command == "quit") {
            break;
        }
        if (isdigit(command)) {
            machine *m = find_machine_by_id(data.root(), std::stoi(command));
            if (m != nullptr) {
                std::cout << "[NAME] " << m->name << " [P] " << (m->worktime / get_worktime(data.root())) << std::endl;
            } else {
                std::cout << "The machine by id is not found." << std::endl;
            }
        } else {
            std::cout << "Incorrect id." << std::endl;
        }
    }
    return 0;
}