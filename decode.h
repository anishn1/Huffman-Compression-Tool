
#ifndef DECODE_H
#define DECODE_H
#include <string>
#include <unordered_map>

int parseSize(std::string& inputFile); // get size of the original size in number of symbols.
std::unordered_map<unsigned char, int> parseFreqTable(std::string& inputFile); // freq table parsed
void decode(std::string& inputFile, std::string& outputFile); // decode using tree traversal

#endif //DECODE_H
