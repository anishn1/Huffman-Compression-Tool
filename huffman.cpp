
#include "huffman.h"

#include <queue>
#include <unordered_map>

Node *buildHuffmanTree(std::unordered_map<unsigned char, int>& freq) {
  std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
  for (int i = 0; i < 256; i++) {
    if (freq[i] > 0) {
      pq.push(new Node(i, freq[i]));
    }
  }
  while (pq.size() > 1) {
    Node *left = pq.top();
    pq.pop();
    Node *right = pq.top();
    pq.pop();
    Node *parent = new Node(0, left->freq + right->freq);
    parent->left = left;
    parent->right = right;
    pq.push(parent);
  }
  Node *root = pq.top();
  return root;
}