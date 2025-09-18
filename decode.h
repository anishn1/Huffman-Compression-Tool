
#ifndef DECODE_H
#define DECODE_H
#include <string>
#include <unordered_map>

#include "huffman.h"

int parseSize(std::string& inputFile); // get size of the original size in number of symbols.
std::unordered_map<unsigned char, int> parseFreqTable(std::string& inputFile); // freq table parsed
void decode(std::string& inputFile, std::string& outputFile, Node *root, int size); // decode using tree traversal

#endif //DECODE_H
