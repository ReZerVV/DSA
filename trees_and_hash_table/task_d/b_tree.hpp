#ifndef B_TREE_H_
#define B_TREE_H_

#include <stddef.h>
#include <iostream>
#include <exception>

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

    void remove(const key_type key) {
        int kindex = 0;
        while (kindex < _size && _key[kindex] < key) {
            kindex += 1;
        }

        if (kindex < _size && _key[kindex] == key) {
            if (_leaf) {
                for (int index = kindex; index < _size-1; ++index) {
                    _key[index] = _key[index+1];
                }
                _size -= 1;
            } else {
                if (_nodes[kindex]->_size >= _degree) {

                    node_b_tree<_Tp> *cur = _nodes[kindex];
                    while (!cur->_leaf) {
                        cur = cur->_nodes[cur->_size];
                    }
                    const int pred = cur->_key[cur->_size-1];
                    _key[kindex] = pred;
                    _nodes[kindex]->remove(pred);

                } else if (_nodes[kindex+1]->_size >= _degree) {

                    node_b_tree<_Tp> *cur = _nodes[kindex+1];
                    while (!cur->_leaf) {
                        cur = cur->_nodes[0];
                    }
                    const int succ = cur->_key[0];
                    _key[kindex] = succ;
                    _nodes[kindex+1]->remove(succ);

                } else {

                    merge(kindex);
                    _nodes[kindex]->remove(_key[kindex]);

                }
            }
        } else {
            if (_leaf) {
                throw std::out_of_range("key does not exist");
            }

            if (_nodes[kindex]->_size < _degree) {
                if (kindex != 0 && _nodes[kindex - 1]->_size >= _degree) {
                    borrow_from_prev(kindex);
                } else if (kindex != _size && _nodes[kindex + 1]->_size >= _degree) {
                    borrow_from_next(kindex);
                } else {
                    if (kindex != _size) {
                        merge(kindex);
                    } else {
                        merge(kindex - 1);
                    }
                }
            }

            if (kindex >= _size) {
                _nodes[kindex - 1]->remove(key);
            }
            else {
                _nodes[kindex]->remove(key);
            }
        }
    }

    void borrow_from_prev(const int index) {
        node_b_tree<_Tp> *child = _nodes[index];
        node_b_tree<_Tp> *sibling = _nodes[index-1];

        for (int i = child->_size-1; i >= 0; --i) {
            child->_key[i+1] = child->_key[i];
        }

        if (!child->_leaf) {
            for (int i = child->_size; i >= 0; --i) {
                child->_nodes[i+1] = child->_nodes[i];
            }
        }

        child->_key[0] = _key[index-1];

        if (!child->_leaf) {
            child->_nodes[0] = sibling->_nodes[sibling->_size];
        }

        _key[index-1] = sibling->_key[sibling->_size-1];

        child->_size += 1;
        sibling->_size -= 1;
    }

    void borrow_from_next(const int index) {
        node_b_tree<_Tp> *child = _nodes[index];
        node_b_tree<_Tp> *sibling = _nodes[index+1];

        child->_key[(child->_size)] = _key[index];

        if (!child->_leaf) {
            child->_nodes[child->_size + 1] = sibling->_nodes[0];
        }

        _key[index] = sibling->_key[0];

        for (int i = 1; i < sibling->_size; ++i) {
            sibling->_key[i-1] = sibling->_key[i];
        }

        if (!sibling->_leaf) {
            for (int i = 1; i <= sibling->_size; ++i) {
                sibling->_nodes[i-1] = sibling->_nodes[i];
            }
        }

        child->_size += 1;
        sibling->_size -= 1;
    }

    void merge(const int index) {
        node_b_tree<_Tp> *child = _nodes[index];
        node_b_tree<_Tp> *sibling = _nodes[index+1];

        child->_key[_degree-1] = _key[index];

        for (int i = 0; i < sibling->_size; ++i)
            child->_key[i+_degree] = sibling->_key[i];

        if (!child->_leaf) {
            for (int i = 0; i <= sibling->_size; ++i) {
                child->_nodes[i+_degree] = sibling->_nodes[i];
            }
        }

        for (int i = index+1; i < _size; ++i) {
            _key[i-1] = _key[i];
        }

        for (int i = index+2; i <= _size; ++i) {
            _nodes[i-1] = _nodes[i];
        }

        child->_size += sibling->_size + 1;
        _size -= 1;

        delete sibling;
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
private:
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
    node_type* search(const key_type key) {
        if (_root == nullptr) {
            return nullptr;
        }
        return _root->search(key);
    }
    
    void remove(const key_type key) {
        if (_root != nullptr) {
            _root->remove(key);
            if (_root->_size == 0) {
                if (_root->_leaf) {
                    _root = nullptr;
                } else {
                    _root = _root->_nodes[0];
                }
                delete _root;
            }
        }
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