
#include "decode.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

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