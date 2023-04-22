#include <iostream>
#include "b_tree.hpp"

int main(int argc, char** argv) {
    b_tree<int> t { 2 };
    
    t.append(10);
    t.append(20);
    t.append(30);
    t.append(40);
    t.append(50);
    t.append(60);
    t.append(70);
    t.append(80);
    t.append(90);
    t.append(100);
    t.append(110);

    std::cout << *t.search(110) << std::endl;
    return 0;
}