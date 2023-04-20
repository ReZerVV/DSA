#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include <stddef.h>

#include <iostream>

template <typename _Tp>
class node_doubly_linked_list {
public:
    template <typename _Tp1>
    friend class doubly_linked_list;
    
    using value_type = _Tp;
public:
// Constructors.
    node_doubly_linked_list()
        :
        _prev(nullptr),
        _next(nullptr) {
    }
    node_doubly_linked_list(node_doubly_linked_list *prev, node_doubly_linked_list *next, const value_type value)
        :
        _prev(prev),
        _next(next),
        _value(value) {
    }
// Movable consrtuctors.
    node_doubly_linked_list(const node_doubly_linked_list&) = default;
// Not movable consrtuctors.
    node_doubly_linked_list(node_doubly_linked_list&&) = default;
// Destructors.
    ~node_doubly_linked_list() {

    }
public:
    node_doubly_linked_list* prev() const { return _prev; }
    node_doubly_linked_list* next() const { return _next; }
    value_type value() const { return _value; }
private:
    node_doubly_linked_list *_prev;
    node_doubly_linked_list *_next;
    value_type              _value;
};

template <typename _Tp>
class doubly_linked_list {
public:    
    using value_type = _Tp;
    using node_type = node_doubly_linked_list<_Tp>;
public:
// Constructors.
    doubly_linked_list()
        :
        _begin(nullptr),
        _end(nullptr),
        _size(0) {
    }
// Movable consrtuctors.
    doubly_linked_list(const doubly_linked_list&) = default;
// Not movable consrtuctors.
    doubly_linked_list(doubly_linked_list&&) = default;
// Destructors.
    ~doubly_linked_list() {
        node_type *node = _begin;
        while (node != nullptr) {
            delete node->_prev;
            node = node->_next;
        }
    }
public:
    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }
    
    node_type* begin() const { return _begin; }
    node_type* end() const { return _end; }

    void append_begin(const value_type value) {
        node_type *node = new node_type{ nullptr, _begin, value };
        if (_begin != nullptr) {
            _begin->_prev = node;   
        } else {
            _end = node;
        }
        _begin = node;
        _size += 1;
    }
    
    void append_end(const value_type value) {
        node_type *node = new node_type{ _end, nullptr, value };
        if (_end != nullptr) {
            _end->_next = node;
        }
        _end = node;
        _size += 1;
    }

    bool insert(const value_type value, const size_t index) {
        if (0 > index && index > _size) {
            return false;
        }
        node_type *node = _begin;
        size_t item_conter = 0;
        while (node != nullptr) {
            if (item_conter == index) {
                node_type *nnode = new node_type{ node, node->_next, value };
                node->_next = nnode;
                if (nnode->_next != nullptr) {
                    nnode->_next->_prev = nnode;
                }
                _size += 1;
                return true;
            }
            node = node->next();
            item_conter += 1;
        }
        return false;
    }
    
    void remove(const size_t index) {

    }

    value_type pop(const size_t index) {

    }
    
    node_type& find(const size_t index) {

    }

    value_type at(const size_t index) {

    }

    friend std::ostream& operator<<(std::ostream &stream, const doubly_linked_list &list) {
        if (!list.empty()) {
            node_type *node = list._begin;
            while (node != nullptr) {
                stream << node->value() << ' ';
                node = node->next();
            }
        }
        return stream;
    }
private:
    size_t      _size;
    node_type   *_begin;
    node_type   *_end;
};

#endif //  DOUBLY_LINKED_LIST_H_