
#include "huffman.h"
#include "encode.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
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

void makeCodes(Node *root, std::string code, std::unordered_map<unsigned char, std::string>& codes) {
  if (!root) {
    return;
  }
  // leaf
  if (!root->left && !root->right) {
    codes[root->c] = code;
    return;
  }
  makeCodes(root->left, code + "0", codes);
  makeCodes(root->right, code + "1", codes);
}
// int originalSize = 0 in the main
std::unordered_map<unsigned char, int> countFreq(const std::string& filename) {
  std::ifstream input(filename, std::ios::binary);
  if (!input) {
    std::cerr << "Error opening file " << filename << std::endl;
  }
  std::unordered_map<unsigned char, int> freqs;
  unsigned char byte;
  while (input.read(reinterpret_cast<char*>(&byte), 1)) {
    freqs[byte]++;
  }
  return freqs;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("Usage: ./huffman <compress|decompress> <input> <output>\n");
    return 1;
  }
  std::string mode = argv[1];
  std::string inputFile = argv[2];
  std::string outputFile = argv[3];

  if (mode == "compress") {
    auto freqs = countFreq(inputFile);
    auto root = buildHuffmanTree(freqs);
    std::unordered_map<unsigned char, std::string> codes;
    makeCodes(root, "", codes);
    encode(inputFile, outputFile, freqs, codes);
    std::cerr << "Encoded file " << outputFile << "\n";
  } else {
    std::cerr << "Unknown mode: " << mode << "\n";
    return 1;
  }
}