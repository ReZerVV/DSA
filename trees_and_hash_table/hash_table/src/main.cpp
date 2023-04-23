#include <iostream>
#include "hash_table.hpp"

struct hash {
    size_t operator()(int value) {
        return value * 12;
    }
};

struct step_hash {
    size_t operator()(int value) {
        return value * 3;
    }
};

int main(int argc, char** argv) {
    hash_table<int, int, hash, step_hash> h{ };
    h.append(1,1);
    h.append(2,1);
    h.append(3,1);
    h.append(4,1);
    h.append(5,1);
    h.append(6,1);
    h.at(1);
    std::cout << h.size() << " : " << h << std::endl;
    return 0;
}