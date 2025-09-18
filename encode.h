
#ifndef ENCODE_H
#define ENCODE_H
#include <string>
#include <unordered_map>

void encode(std::string& inputFile, std::string& outputFile, std::unordered_map<unsigned char, int>& freqs, std::unordered_map<unsigned char, std::string>& codes);

#endif //ENCODE_H
