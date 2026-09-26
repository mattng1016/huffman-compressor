#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <array>

#include "bitWriter.h"

struct BitWriter {
  FILE* file;
  uint8_t buffer = 0;
  int bitsUsed = 0;

  void writeBit(bool bit) {
    buffer = (buffer << 1) | (bit ? 1 : 0);
    bitsUsed++;

    if (bitsUsed == 8) {
      fputc(buffer, file);
      buffer = 0;
      bitsUsed = 0;
    }
  }

  void writeByte(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
      writeBit((value >> i) & 1);
    }
  }

  void flush() {
    if (bitsUsed > 0) {
      buffer <<= (8 - bitsUsed);
      fputc(buffer, file);
      buffer = 0;
      bitsUsed = 0;
    }
  }
};

void writeTree(BitWriter& out, const Node* node) {
  if (node->left == nullptr && node->right == nullptr) {
    out.writeBit(1);
    out.writeByte(node->value);
    return;
  }

  out.writeBit(0);
  writeTree(out, node->left);
  writeTree(out, node->right);
}

FILE* newFile(const char* path, std::array<std::string, 256> &table, Node* root, uint64_t originalSize)  {
  std::string s(path);
  s = s + ".huff";
  const char* p = s.c_str();

  FILE* huffFile = std::fopen(p, "w+b");
  FILE* oldFile = std::fopen(path, "rb");

  fwrite(&originalSize, sizeof(originalSize), 1, huffFile); 

  BitWriter out {huffFile};

  writeTree(out, root);
  
  // Writing compressed bits into file
  int byte;
  while ((byte = fgetc(oldFile)) != EOF) {
    for (char bit : table[static_cast<unsigned char>(byte)]) {
      out.writeBit(bit == '1');
    }  
  }
  out.flush();
  fclose(oldFile);
  fclose(huffFile);
  return nullptr;
}


