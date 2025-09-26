# Huffman-Compression-Tool

A command-line utility in C++ for the compression and decompression of files using Huffman coding.

## Features

- **Lossless compression** of text and binary files.
- **Huffman tree construction** from frequency analysis of the input file.
- **Bit-level file encoding** for efficient storage.
- Includes metadata consisting of original file size and frequency table to ensure correct decompression.
- Modular design: separate `encode` and `decode` functionality.

## File Structure

```bash
Huffman-Compression-Tool/
├── huffman.cpp   # Main program + Tree building functions
├── huffman.h     # Node structure and Huffman tree comparator
├── encode.cpp    # File encoding functions
├── encode.h
├── decode.cpp    # File decoding functions
├── decode.h
└── README.md
```

## Installation and Building

```bash
git clone https://github.com/anishn1/Huffman-Compression-Tool.git
g++ huffman.cpp encode.cpp decode.cpp -o huffman
```

## Usage

#### Compression

```bash
./huffman compress <input_file> <output_file.huff>
```

Example:

```bash
./huffman compress ../text.txt compressed.huff
```

#### Decompression

```bash
./huffman decompress <input_file.huff> <output_file>
```

Example:

```bash
./huffman decompress compressed.huff recovered.txt
```
