#include <iostream>
#include "hash_table.hpp"

struct hash {
    size_t operator()(int value) {
        return value * 99 % 100;
    }
};

int main(int argc, char** argv) {
    hash_table<int, int, hash> h{ };
    h.append(1,1);
    h[2] = 10;
    std::cout << h.at(2) << std::endl;
    return 0;
}