#include <iostream>
#include "b_tree.hpp"

int main(int argc, char** argv) {
    b_tree<int> t { 2 };
    
    t.append(10);
    t.append(20);
    t.append(30);
    t.append(40);
    t.append(50);
    t.append(51);
    t.append(56);
    t.append(45);

    t.remove(45);

    std::cout << t << std::endl;
    return 0;
}