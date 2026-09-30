#include <cstddef>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "compressor.h"
#include "decompressor.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: Usage: ./fileCompressor <file>\n");
    exit(0);
  }
  std::array<std::string, 256> path;

  compressor(argv[1]);
  std::string h = argv[1];
  h = h + ".huff";
  decompressor(h.c_str());

 return 0;
}
