
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <unordered_map>

struct Node {
  unsigned char c;
  int freq;
  Node *left;
  Node *right;

  Node(unsigned char c, int f) : c(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
  bool operator()(const Node *a, const Node *b) const {
    return a->freq > b->freq;
  }
};

Node *buildHuffmanTree(std::unordered_map<unsigned char, int>& freq);
void makeCodes(Node *root, std::string code, std::unordered_map<unsigned char, std::string>& codes);
std::unordered_map<unsigned char, int> countFreq(const std::string& filename);

#endif //HUFFMAN_H
