#include <array>
#include "decompressor.h"
#include "huffmanTree.h"

void decompressor(const char* path) {
  FILE* decompressed = fopen("decompressed.txt", "w+b");  
  FILE* compressed = fopen(path, "rb");
  HuffmanTree t;


}
