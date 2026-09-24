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

  compressor(argv[1]);

 return 0;
}
