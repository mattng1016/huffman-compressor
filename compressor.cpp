#include <array>
#include <cstddef>
#include <string>
#include <sys/stat.h>

#include "bitReader.h"
#include "bitWriter.h"
#include "huffmanTree.h"

bool validatePath(const char* path) {
  struct stat buffer;
  if (stat(path, &buffer) == -1) {
    return false;
  }
  return true;
} 

void compressor(const char* p) {
  if (!validatePath(p)) {
    printf("Error: Invalid path: %s\n", p);
    exit(0);
  }
  u_int64_t *arr = readBit(p);
  std::array<std::string, 256> path;
  HuffmanTree t;
  t.build(arr);
  t.buildBits(t.root, "", path);
  newFile(p, path);
  
  free(arr);
}
