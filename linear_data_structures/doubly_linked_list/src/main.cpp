#include <iostream>
#include "doubly_linked_list.hpp"

int main(int argc, char** argv) {
    doubly_linked_list<int> list;
    list.append_begin(1);
    list.append_end(2);
    std::cout << list.insert(0, 1) << std::endl;
    std::cout << "doubly_linked_list: " << list << std::endl;
    return 0;
}