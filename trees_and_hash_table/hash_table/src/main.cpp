#include <iostream>
#include "hash_table.hpp"

struct hash {};

int main(int argc, char** argv) {
    hash_table<int, int, hash> h{ };
    h.append(10,10);
    h[1] = 100;
    std::cout << h[1] << std::endl;
    return 0;
}