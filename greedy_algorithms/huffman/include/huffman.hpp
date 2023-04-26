#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <stddef.h>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

namespace huffman
{
    struct huffman_node {
        char            _sym;
        size_t          _frequency;
        huffman_node    *_left;
        huffman_node    *_right;
    };
    struct compare {
        bool operator()(const huffman_node *node_first, const huffman_node *node_second) {
            return node_first->_frequency > node_second->_frequency;
        }
    };
    
    huffman_node *_root = nullptr;
    
    void to_huffman_code(huffman_node *node, std::vector<std::string> &result, std::string prefix = "") {
        if (node->_sym != '*') {
            result[static_cast<size_t>(node->_sym)] = prefix;
            return;
        }
        to_huffman_code(node->_left, result, prefix + "0");
        to_huffman_code(node->_right, result, prefix + "1");
    }
    std::vector<std::string> huffman_tree_builder(const std::vector<size_t> &frequencies) {
        std::priority_queue<huffman_node*, std::vector<huffman_node*>, compare> nodes{  };
        for (size_t index = 0; index < 128; ++index) {
            if (frequencies[index] != 0) {
                nodes.push(new huffman_node{ static_cast<char>(index), frequencies[index], nullptr, nullptr });
            }
        }

        while (nodes.size() > 1) {
            huffman_node *right = nodes.top();
            nodes.pop();
            huffman_node *left = nodes.top();
            nodes.pop();

            nodes.push(new huffman_node{ '*', left->_frequency + right->_frequency, left, right });
        }
        
        std::vector<std::string> result{  };
        result.resize(128);
        for (size_t index = 0; index < 128; ++index) {
            result[index] = std::string{  };
        }

        _root = nodes.top();
        to_huffman_code(_root, result);

        return result;
    }

    std::string encode(const std::string data) {
        std::string result{  };

        std::vector<size_t> frequencies{  };
        frequencies.resize(128);
        for (size_t index = 0; index < 128; ++index) {
            frequencies[index] = 0;
        }
        for (auto it = data.begin(); it != data.end(); ++it) {
            frequencies[(size_t)*it] += 1;
        }

        std::vector<std::string> codes = huffman_tree_builder(frequencies);

        for (auto it = data.begin(); it != data.end(); ++it) {
            result.append(codes[static_cast<size_t>(*it)]);
        }

        return result;
    }
    std::string decode(const std::string data) {
        if (_root == nullptr) {
            std::cout << "[Error::huffman::decode]  huffman tree is nullptr." << std::endl;
            return std::string{  };
        }
        std::string result{  };

        huffman_node *curr_node = _root;
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (*it == '0') {
                curr_node = curr_node->_left;
            } else {
                curr_node = curr_node->_right;
            }
            if (curr_node->_left == nullptr && curr_node->_right == nullptr) {
                char c_str[1] = { curr_node->_sym };
                result.append(c_str);
                curr_node = _root;
            }
        }

        return result;
    }
}

#endif // HUFFMAN_H_