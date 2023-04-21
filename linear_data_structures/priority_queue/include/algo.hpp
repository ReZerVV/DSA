#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_

#include <stddef.h>

template <typename _Tp>
void swap(_Tp *first_value, _Tp *second_value) {
    _Tp temp_value = *second_value;
    *second_value = *first_value;
    *first_value = temp_value;
}

template <typename _Tp>
void print_array(_Tp *buffer, const size_t size) {
    for (size_t index = 0; index < size; ++index) {
        std::cout <<  buffer[index] << ' ';
    }
    std::cout << std::endl;
}

template <typename _Tp, typename _Cmp>
void heapify(_Tp *buffer, const size_t size, const size_t index, _Cmp compare) {
    int largest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    
    if (left_child < size && compare(buffer[left_child], buffer[largest])) {
        largest = left_child;
    }

    if (right_child < size && compare(buffer[right_child], buffer[largest])) {
        largest = right_child;
    }

    if (largest != index) {
        swap(&buffer[index], &buffer[largest]);
        heapify(buffer, size, largest, compare);
    }
}

template <typename _Tp, typename _Cmp>
void heap_sort(_Tp *buffer, const size_t size, _Cmp compare) {
    for (int index = size / 2 - 1; index >= 0; index--) {
      heapify(buffer, size, index, compare);
    }
    for (int index = size - 1; index >= 0; index--) {
      swap(&buffer[0], &buffer[index]);
      heapify(buffer, index, 0, compare);
    }
}

#endif // HEAP_SORT_H_