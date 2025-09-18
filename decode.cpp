
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

