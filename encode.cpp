
#include "encode.h"

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

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
