
#ifndef HUFFMAN_H
#define HUFFMAN_H

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

#endif //HUFFMAN_H
