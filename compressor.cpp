#include <array>
#include <cstddef>
#include <string>
#include <sys/stat.h>

#include "bitReader.h"
#include "bitWriter.h"
#include "compressor.h"

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
  struct stat info;
  stat(p, &info);
  uint64_t originalSize = info.st_size;
  std::array<std::string, 256> path;
  u_int64_t *arr = readBit(p);
  HuffmanTree t;
  t.build(arr);
  t.buildBits(t.root, "", path);
  FILE* f = newFile(p, path, t.root, originalSize); 
   

  free(arr);
}
