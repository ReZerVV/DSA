#include <iostream>
#include "priority_queue.hpp"

struct compare {
    bool operator()(int first_value, int second_value) {
        return first_value < second_value;
    }
}; 

int main(int argc, char** argv) {
    priority_queue<int, compare> h{ };
    h.append(1);
    h.append(1);
    h.append(1);
    h.append(10);
    h.append(10);

    std::cout << "remove: ";
    std::cout << h.peek() << std::endl;
    h.remove(1);

    std::cout << "pop: ";
    while (!h.empty()) {
        std::cout << h.pop() << ' ';
    }
    std::cout << std::endl;

    std::cout << "heap: " << h << "size: " << h.size() << std::endl;
    
    h.clear();
    
    int size = 10;
    int *buffer = new int[size];
    for (size_t i=0; i<size; ++i)
        buffer[i] = i;

    h.array(buffer, size);

    std::cout << "heap: " << h << "size: " << h.size() << std::endl;
    delete buffer;
    return 0;
}