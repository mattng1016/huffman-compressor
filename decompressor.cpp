#include <cstdio>
#include <cstdint>
#include <pthread.h>
#include "decompressor.h"
#include "huffmanTree.h"

struct BitReader {
  FILE* file;
  uint8_t buffer = 0;
  int bitsLeft = 0;

  int readBit() {
    if (bitsLeft == 0) {
      int nextByte = fgetc(file);
      if (nextByte == EOF) {
        return -1;
      }
      buffer = static_cast<uint8_t>(nextByte);
      bitsLeft = 8;
    }
    int bit = (buffer >> (bitsLeft - 1)) & 1;
    bitsLeft--;
    return bit;
  }
};

Node* readNode(BitReader& bits) {
  int marker = bits.readBit();
  if (marker == -1) return nullptr;

  if (marker == 1) {
    uint8_t value = 0;
    for (int i = 0; i < 8; i++) {
      int bit = bits.readBit();
      value <<= 1;
      value = static_cast<unsigned int>(value | bit);
    }
    return new Node{value, 0, nullptr, nullptr};
  }

  Node* node = new Node{0, 0, nullptr, nullptr};
  node->left = readNode(bits);
  node->right = readNode(bits);

  return node;
}

bool isLeaf(Node* node) {
  if (node->left == nullptr && node->right == nullptr) {
    return true;
  }
  return false;
}

void decompressor(const char* path) {
  FILE* decompressed = fopen("decompressed.txt", "w+b");  
  FILE* compressed = fopen(path, "rb");
  HuffmanTree t;

  uint64_t size = 0;
  std::fread(&size, sizeof(size), 1, compressed);
  std::cout << "Size: " << size;

  BitReader bits{compressed};
  Node* root = readNode(bits);
  
  Node* current = root;
  int done = 0;

  // If huffman tree's root is only node (file has one type of char)
  if (isLeaf(current)) {
    for (int i = 0; i < size; i++) {
      fputc(current->value, decompressed);
    }
    return;
  }

  while (done < size) {
    if (current->left == nullptr && current->right == nullptr) {
      fputc(current->value, decompressed);
      current = root;
      done++;
    } 
    int b = bits.readBit();
    if (b == 1) {
      current = current->right;
    } else if (b == 0) {
      current = current->left;
    } 
  }
}
