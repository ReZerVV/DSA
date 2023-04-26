#include "huffman.hpp"

int main(int argc, char** argv) {
    std::string data = "hello world hello hello hello.";
    std::string encode_data = huffman::encode(data);
    std::cout << encode_data << std::endl;
    std::string decode_data = huffman::decode(encode_data);
    std::cout << decode_data << std::endl;
    return 0;
}