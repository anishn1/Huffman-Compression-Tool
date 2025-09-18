
#include "decode.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "huffman.h"

int parseSize(std::string& inputFile) {
  std::ifstream input(inputFile, std::ios::binary);
  if (!input) {
    std::cerr << "Error opening file " << inputFile << std::endl;
    return -1;
  }
  uint64_t size;
  input.read(reinterpret_cast<char *>(&size), 8);
  return size;
}

std::unordered_map<unsigned char, int> parseFreqTable(std::string& inputFile) {
  std::ifstream input(inputFile, std::ios::binary);
  input.seekg(sizeof(uint64_t), std::ios::beg);
  std::unordered_map<unsigned char, int> freqs;
  for (int i = 0; i < 256; i++) {
    int freq;
    input.read(reinterpret_cast<char*>(&freq), sizeof(int));
    freqs[i] = freq;
  }
  return freqs;
}

void decode(std::string& inputFile, std::string& outputFile, Node *root, int origSize) {
  std::ifstream input(inputFile, std::ios::binary);
  if (!input) {
    std::cerr << "Error opening file " << inputFile << std::endl;
    return;
  }
  std::ofstream output(outputFile, std::ios::binary);
  if (!output) {
    std::cerr << "Error creating file " << outputFile << std::endl;
    return;
  }
  unsigned char byte;
  int bitCount = 0;
  int size = 0;
  while (size < origSize) {
    Node *curr = root;
    while (curr->left || curr->right) {
      if (bitCount == 0) {
        input.read(reinterpret_cast<char *>(&byte), 1);
        bitCount = 8;
      }
      int bit = (byte >> (bitCount-1)) & 0x1;
      if (bit) {
        curr = curr->right;
      } else {
        curr = curr->left;
      }
      bitCount--;
    }
    output.write(reinterpret_cast<char *>(&curr->c), 1);
    size++;
  }
  input.close();
  output.close();
}

// size = parseSize(inputFile);
// freqs = parseFreqTable(inputFile);
// Node *root = buildHuff(freqs);
// decode(inputFile, outputFile, root);