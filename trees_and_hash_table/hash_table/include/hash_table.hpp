#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <iostream>
#include <stddef.h>
#include <malloc.h>
#include <cstring>
#include <exception>

template <typename _vTp, typename _kTp>
class node_hash_table {
public:
    template <typename _vTp1, typename _kTp1, typename _hFunc>
    friend class hash_table;

    using value_type = _vTp;
    using key_type = _kTp;
public:
// Constructors.
    node_hash_table()
        :
        _state(false) {
    }
    node_hash_table(key_type key, value_type value)
        :
        _key(key),
        _value(value),
        _state(true) {
    }
// Not movable constructos.
    node_hash_table(const node_hash_table &other)
        :
        _key(other._key),
        _value(other._value),
        _state(other._state) {
    }
    node_hash_table& operator=(const node_hash_table &other) {
        _key = other._key;
        _value = other._value;
        _state = other._state;
        return *this;
    }
    node_hash_table& operator=(const value_type value) {
        _value = value;
        _state = true;
        return *this;
    }
// Movable constructors.
    node_hash_table(node_hash_table&&) = default;
// Destructros.
    ~node_hash_table() = default;
public:
    friend std::ostream& operator<<(std::ostream &stream, const node_hash_table &node) {
        stream << node._value << ' ';
        return stream;
    }
    bool state() const { return _state; }
    key_type key() const { return _key; }
    key_type value() const { return _value; }
private:
    bool        _state;
    key_type    _key;
    value_type  _value;
};

#define HASH_TABLE_BUFFER_CAPACITY_ 2
template <typename _vTp, typename _kTp, typename _hFunc>
class hash_table {
public:
    using value_type = _vTp;
    using key_type = _kTp;
    using hash_func_type = _hFunc;
    using node_type = node_hash_table<_vTp, _kTp>;
public:
// Constructors.
    hash_table()
        :
        _capacity(HASH_TABLE_BUFFER_CAPACITY_),
        _size(0),
        _buffer(new node_type[HASH_TABLE_BUFFER_CAPACITY_]) {

    }
// Not movable constructos.
    hash_table(const hash_table&) = default;
    hash_table& operator=(const hash_table&) = default;
// Movable constructors.
    hash_table(hash_table&&) = default;
// Destructors.
    ~hash_table() {
        mem_free();
    }
public:
    size_t capacity() const { return _capacity; }
    
    size_t size() const { 
        size_t size = 0;
        for (size_t index = 0; index < _capacity; ++index) {
            if (_buffer[index]._state) {
                size += 1;
            }
        }
        return size; 
    }
    
    size_t empty() const { return size() == 0; }

    bool contains(const key_type key) {
        if (empty()) {
            return false;
        }
        for (size_t index = 0; index < _capacity; ++index) {
            if (_buffer[index]._state && _buffer[index]._key == key) {
               return true;
            }
        }
        return false;
    }

    void append(key_type key, value_type value) {
        if (size() >= _capacity) {
            mem_reallocation();
        }
        size_t index = _hash(key) % _capacity;
        if (!_buffer[index]._state) {
            _buffer[index] = node_type{key, value};
            _size += 1;
            return;
        }
        if (contains(key)) {
            throw std::out_of_range("item already exists");
        }
        while (true) {
            index = (index + 1) % _capacity;
            if (!_buffer[index]._state) {
                _buffer[index] = node_type{key, value};
                _size += 1;
                return;
            }
        }
    }

    void remove(key_type key) {
        if (!empty()) {
            size_t index = _hash(key) % _capacity;
            if (!_buffer[index]._state) {
                throw std::out_of_range("item is not found");
            }
            if (_buffer[index]._state && _buffer[index]._key == key) {
                _buffer[index]._state = false;
                _size -= 1;
                return;
            }
            if (!contains(key)) {
                throw std::out_of_range("item already exists");
            }
            while (true) {
                index = (index + 1) % _capacity;
                if (_buffer[index]._state && _buffer[index]._key == key) {
                    _buffer[index]._state = false;
                    _size -= 1;
                    return;
                }
            }
        }
    }
    
    node_type& at(const key_type key) {
        if (!empty()) {
            size_t index = _hash(key) % _capacity;
            if (!_buffer[index]._state) {
                throw std::out_of_range("item is not found");
            }
            if (_buffer[index]._state && _buffer[index]._key == key) {
                return _buffer[index];
            }
            while (contains(key)) {
                index = (index + 1) % _capacity;
                if (_buffer[index]._state && _buffer[index]._key == key) {
                    return _buffer[index];
                }
            }
            throw std::out_of_range("item is not found");
        }
        throw std::out_of_range("hash table is empty");
    }

    node_type& operator[](const key_type key) {
        size_t index = 0;
        if (contains(key)) {
            return at(key);
        } else {
            if (_size >= _capacity) {
                mem_reallocation();
            }
            size_t index = _hash(key) % _capacity;
            if (!_buffer[index]._state) {
                _buffer[index]._key = key;
                return _buffer[index];
            }
            while (true) {
                index = (index + 1) % _capacity;
                if (!_buffer[index]._state) {
                    _buffer[index]._key = key;
                    return _buffer[index];
                }
            }
        }
    }

    friend std::ostream& operator<<(std::ostream &stream, const hash_table &hash_table) {
        if (!hash_table.empty()) {
            for (size_t index = 0; index < hash_table.capacity(); ++index) {
                if (hash_table._buffer[index].state()) {
                    stream << hash_table._buffer[index] << ' ';
                }
            }
        }
        return stream;
    }
private:
    void mem_reallocation() {
        _capacity *= 2;
        node_type *new_buffer = new node_type[_capacity];
        for (size_t index = 0; index < _size; ++index) {
            new_buffer[index] = _buffer[index];
        }
        delete _buffer;
        _buffer = new_buffer;
    }
    void mem_free() {
        delete[] _buffer;
    }
private:
    size_t          _capacity;
    size_t          _size;
    node_type       *_buffer;
    hash_func_type  _hash;
};

#endif // HASH_TABLE_H_