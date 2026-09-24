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

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: Usage: ./fileCompressor <file>\n");
    exit(0);
  }
  if (!validatePath(argv[1])) {
    printf("Error: Invalid path: %s\n", argv[1]);
    exit(0);
  }
  u_int64_t *arr = readBit(argv[1]);
  std::array<std::string, 256> path;
  HuffmanTree t;
  t.build(arr);
  t.buildBits(t.root, "", path);
  newFile(argv[1], path);
  

  free(arr);
  return 0;
}
