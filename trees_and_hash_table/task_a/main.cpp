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

std::vector<machine> machine_data_from_file(const char* file_path) {
    std::ifstream file;
    file.open(file_path);
    if (!file.is_open()) {
        std::cout << "File is not open: " << file_path << std::endl;
        return std::vector<machine>{  };
    }
    std::vector<machine> data{  };
    std::string line{  };
    while (getline(file, line)) {
        data.push_back(machine{  });
    }
    file.close();
    return data;
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



int main(int argc, char** argv) {
    b_tree<machine> t{ 2 };
    t.append(machine{ 0, "0", (machine_type)MT_1, 0, 10 });
    t.append(machine{ 1, "1", (machine_type)MT_1, 0, 10 });
    t.append(machine{ 2, "2", (machine_type)MT_1, 0, 10 });
    t.append(machine{ 3, "3", (machine_type)MT_1, 0, 10 });
    t.append(machine{ 4, "4", (machine_type)MT_1, 0, 10 });
    std::cout << get_worktime(t.root()) << std::endl;   
    return 0;
}