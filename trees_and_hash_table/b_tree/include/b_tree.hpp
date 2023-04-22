#ifndef B_TREE_H_
#define B_TREE_H_

#include <stddef.h>
#include <iostream>

template <typename _Tp>
class node_b_tree {
public:
    template <typename _b_treeTp>
    friend class b_tree;

    using key_type = _Tp;
public:
    node_b_tree(const int degree, const bool leaf)
        :
        _degree(degree),
        _size(0),
        _leaf(leaf) {
        _key = new key_type[degree*2-1];
        _nodes = new node_b_tree*[degree*2];
    }
// Not movable constructors.
    node_b_tree(const node_b_tree&) = default;
    node_b_tree& operator=(const node_b_tree&) = default;
// Movable constructors.
    node_b_tree(node_b_tree&&) = default;
    ~node_b_tree() {
        delete[] _key;
        delete[] _nodes;
    }
public:
    node_b_tree* search(const key_type key) {
        int index = 0;
        while (index < _size && key > _key[index]) {
            index++;
        }
        if (key == _key[index]) {
            return this;
        }

        if (_leaf == true) {
            return nullptr;
        }
        
        return _nodes[index]->search(key);
    }

    void append(const key_type key) {
        int index = _size - 1;

        if (_leaf == true) {
            while (index >= 0 && _key[index] > key) {
                _key[index + 1] = _key[index];
                index--;
            }
            
            _key[index + 1] = key;
            _size += 1;
        } else {
            while (index >= 0 && _key[index] > key) {
                index--;
            }
            
            if (_nodes[index + 1]->_size == 2 * _degree - 1) {
                split(index + 1, _nodes[index + 1]);

                if (_key[index + 1] < key) {
                    index++;
                }
            }
            _nodes[index + 1]->append(key);
        }
    }
    
    void split(const int index, node_b_tree* snode) {
        node_b_tree *node = new node_b_tree(snode->_degree, snode->_leaf);
        node->_size = _degree - 1;

        for (int j = 0; j < _degree - 1; j++) {
            node->_key[j] = snode->_key[j + _degree];
        }

        if (snode->_leaf == false) {
            for (int j = 0; j < _degree; j++) {
                node->_nodes[j] = snode->_nodes[j + _degree];
            }
        }

        snode->_size = _degree - 1;

        for (int j = _size; j >= index + 1; j--) {
            _nodes[j + 1] = _nodes[j];
        }

        _nodes[index + 1] = node;

        for (int j = _size - 1; j >= index; j--) {
            _key[j + 1] = _key[j];
        }

        _key[index] = snode->_key[_degree - 1];
        _size += 1;
    }

    friend std::ostream& operator<<(std::ostream &stream, const node_b_tree &node_b_tree) {
        int index = 0;
        for (index = 0; index < node_b_tree._size; ++index) {
            if (node_b_tree._leaf == false) {
                operator<<(stream, *node_b_tree._nodes[index]);
            }
            stream << node_b_tree._key[index] << ' ';
        }
        
        if (node_b_tree._leaf == false) {
            operator<<(stream, *node_b_tree._nodes[index]);
        }
        return stream;
    }
public:
    int          _degree;
    int          _size;
    key_type        *_key;
    node_b_tree     **_nodes;
    bool            _leaf;
};

template <typename _Tp>
class b_tree {
public:
    using key_type = _Tp;
    using node_type = node_b_tree<_Tp>;
public:
    b_tree(int degree)
        :
        _degree(degree),
        _root(nullptr) {

    }
// Not movable constructors.
    b_tree(const b_tree&) = default;
    b_tree& operator=(const b_tree&) = default;
// Movable constructors.
    b_tree(b_tree&&) = default;
    ~b_tree() {
        delete _root;
    }
public:
    node_type* search(const int key) {
        if (_root == nullptr) {
            return nullptr;
        }
        return _root->search(key);
    }
    
    void remove(const int key) {

    }

    void append(const key_type key) {
        if (_root == nullptr) {
            _root = new node_type(_degree, true);
            _root->_key[0] = key;
            _root->_size = 1;
        } else {
            if (_root->_size == 2 * _degree - 1) {
                node_type *node = new node_type(_degree, false);

                node->_nodes[0] = _root;

                node->split(0, _root);

                int index = 0;
                if (node->_key[0] < key) {
                    index++;
                }

                node->_nodes[index]->append(key);

                _root = node;
            } else {
                _root->append(key);
            }
        }
    }

    friend std::ostream& operator<<(std::ostream &stream, const b_tree &b_tree) {
        if (b_tree._root != nullptr) {
            stream << *b_tree._root;
        }
        return stream;
    }
private:
    int      _degree;
    node_type   *_root;
};

#endif // B_TREE_H_