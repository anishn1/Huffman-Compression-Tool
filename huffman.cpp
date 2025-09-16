
#include "huffman.h"

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

void encode(std::string& inputFile, std::string& outputFile, std::unordered_map<unsigned char, int>& freqs, std::unordered_map<unsigned char, std::string>& codes) {
  std::ifstream input(inputFile, std::ios::binary | std::ios::ate);
  if (!input) throw std::runtime_error("Could not open input file");

  std::ofstream output(outputFile, std::ios::binary);
  if (!output) throw std::runtime_error("Could not create output file");

  // origSize added
  std::streamsize inputSize = input.tellg();
  input.seekg(0);
  output.write(reinterpret_cast<char*>(&inputSize), sizeof(std::streamsize));

  // freqTable added
  for (int i = 0; i < 256; i++) {
    int freq = freqs[i];
    output.write(reinterpret_cast<char*>(&freq), sizeof(int));
  }

  // added codes for each char
  unsigned char byte;
  unsigned char buff = 0;
  int bitCount = 0;
  while (input.read(reinterpret_cast<char*>(&byte), 1)) {
    std::string& code = codes[byte];
    for (char c : code) {
      buff <<= 1;
      if (c == '1') {
        buff |= 1;
      }
      bitCount++;
      if (bitCount == 8) {
        output.write(reinterpret_cast<char*>(&buff), 1);
        bitCount = 0;
        buff = 0;
      }
    }
  }
  if (bitCount > 0) {
    buff <<= 8 - bitCount;
    output.write(reinterpret_cast<char*>(&buff), 1);
  }
}