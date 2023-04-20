#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <stddef.h>
#include <malloc.h>
#include <cstring>

template <typename _Tp>
void swap(_Tp *first_value, _Tp *second_value) {
    _Tp temp_value = *second_value;
    *second_value = *first_value;
    *first_value = temp_value;
}

#define BUFFER_CAPACITY_ 1

template <typename _Tp, typename _Cmp>
class priority_queue {
public:
    using value_type = _Tp;
    using compare_type = _Cmp;
public:
// Constructors.
    priority_queue()
        :
        _capacity(BUFFER_CAPACITY_),
        _size(0),
        _buffer(new value_type[BUFFER_CAPACITY_]) {
    }
// Not movable constructors.
    priority_queue(const priority_queue&) = default;
// Movable constructrors.
    priority_queue(priority_queue&&) = default;
// Destructos.
    ~priority_queue() {
        mem_free();
    }
public:
    size_t capacity() const { return _capacity; }
    
    size_t size() const { return _size; }
    
    bool empty() const { return _size == 0; }
    
    value_type peek() const { return _buffer[0]; }

    void clear() { _size = 0; }

    void append(const value_type value) {
        if (_size >= _capacity) {
            mem_reallocation();
        }
        _buffer[_size] = value;
        _size += 1;
        if (!empty()) {
            for (int index = _size / 2 - 1; index >= 0; --index) {
                heapify(index);
            }
        }
    }
    
    void remove(value_type value) {
        if (empty()) {
            return;
        }

        int index = 0;
        for (index = 0; index < _size; ++index) {
            if (_buffer[index] == value) {
                break;
            }
        }

        swap(&_buffer[index], &_buffer[_size-1]);
        _size -= 1;
        
        for (index = _size / 2 - 1; index >= 0; --index) {
            heapify(index);
        }
    }

    value_type pop() {
        if (empty()) {
            return NULL;
        }

        swap(&_buffer[0], &_buffer[_size-1]);
        _size -= 1;

        for (int index = _size / 2 - 1; index >= 0; --index) {
            heapify(index);
        }
        return _buffer[_size];
    }
    
    void sort() {
        for (int index = 0; index < _size; ++index) {
            heapify(index);
        }
    }
    
    void array(value_type *buffer, const size_t size) {
        delete _buffer;
        _capacity = size;
        _buffer = new value_type[_capacity];
        _size = size;
        for (size_t index = 0; index < _size; ++index) {
            _buffer[index] = buffer[index];
        }
        sort();
    }

    friend std::ostream& operator<<(std::ostream &stream, const priority_queue &priority_queue) {
        if (!priority_queue.empty()) {
            for (size_t index = 0; index < priority_queue._size; ++index) {
                stream << priority_queue._buffer[index] << ' ';
            }
        }
        return stream;
    }
private:
    void heapify(const size_t index) {
        int largest = index;
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        
        if (left_child < _size && _compare(_buffer[left_child], _buffer[largest])) {
            largest = left_child;
        }
    
        if (right_child < _size && _compare(_buffer[right_child], _buffer[largest])) {
            largest = right_child;
        }
    
        if (largest != index) {
            std::swap(_buffer[index], _buffer[largest]);
            heapify(largest);
        }
    }

    void mem_reallocation() {
        _capacity *= 2;
        _buffer = static_cast<value_type*>(realloc(_buffer, _capacity));
    }
    
    void mem_free() {
        delete _buffer;
    }
private:
    size_t          _capacity;
    size_t          _size;
    value_type      *_buffer;
    compare_type    _compare;
};

#endif // HEAP_H_