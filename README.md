# Huffman File Compressor

A small C++ project that compresses a file with Huffman coding and then decompresses the generated archive. It builds a Huffman tree from the input byte frequencies, writes a serialized tree and the original file size into the archive, and encodes the input bytes using the tree paths.

## Build

Compile the source files with a C++ compiler:

```sh
g++ -std=c++17 main.cpp compressor.cpp decompressor.cpp huffmanTree.cpp bitReader.cpp bitWriter.cpp -o fileCompressor
```

## Run

```sh
./fileCompressor <file>
```

## Archive layout

The `.huff` file contains:

1. The original file size
2. A preorder tree description, bit-packed: `0` means an internal node; `1` means a leaf followed by its 8-bit byte value
3. The Huffman-encoded input bits

