# Huffman File Compressor

A small C++ project that compresses a file with Huffman coding and then decompresses the generated archive. It builds a Huffman tree from the input byte frequencies, writes a serialized tree and the original file size into the archive, and encodes the input bytes using the tree paths.

## Build

Compile the source files with a C++ compiler:

```sh
g++ -std=c++17 main.cpp compressor.cpp decompressor.cpp huffmanTree.cpp bitReader.cpp bitWriter.cpp -o fileCompressor
```

## Run

```sh
./fileCompressor path/to/input-file
```

The program writes the archive beside the input as `path/to/input-file.huff`. It also decompresses that archive to `decompressed.txt` in the current working directory, overwriting that file each time it runs.

## Archive layout

The `.huff` file contains:

1. The original file size as an 8-byte integer.
2. A preorder tree description, bit-packed: `0` means an internal node; `1` means a leaf followed by its 8-bit byte value.
3. The Huffman-encoded input bits, padded with zero bits at the end to complete the final byte.

The decoder reads the original size to know when it has produced the original number of bytes, so final padding bits are ignored.

## Current limitations

- The format writes the size in the host machine’s byte order, so archives are not guaranteed to be portable between systems with different byte orders.
- Empty input currently has no Huffman tree and is not supported safely.
- A file containing only one distinct byte value needs special handling in the decoder; its tree has one leaf and its encoded code is empty.
- The current program always creates `decompressed.txt` in the working directory.
