#include <iostream>

// Test priority queue.
#if true

#include "priority_queue.hpp"

struct compare {
    bool operator()(int first_value, int second_value) {
        return first_value < second_value;
    }
}; 

int main(int argc, char** argv) {
    priority_queue<int, compare> h{ };
    h.append(9);
    h.append(2);
    h.append(6);
    h.append(100);
    h.append(10);

    std::cout << "pop: ";
    while (!h.empty()) {
        std::cout << h.pop() << ' ';
    }
    std::cout << std::endl;

    std::cout << "heap: " << h << "size: " << h.size() << std::endl;
    return 0;
}

#endif

// Heap sort.
#if false

#include <stddef.h>
#include "algo.hpp"

struct compare {
    bool operator()(int first_value, int second_value) {
        return first_value < second_value;
    }
}; 

int main(int argv, char** argc) {
    int buffer[] = { 12,5,6,85,23,65 };
    size_t size = sizeof(buffer) / sizeof(buffer[0]);

    print_array(buffer, size);
    heap_sort(buffer, size, compare{  });
    print_array(buffer, size);
    
    return 0;
}

#endif