#include "bitReader.h"
#include <cstdio>

uint64_t* readBit(const char* path) {
  uint64_t *arr = new uint64_t[256];
  FILE* f = fopen(path, "rb");
  if (!f) {
    printf("Reading %s error", path);
  }
  int c;
  while ((c = fgetc(f)) != EOF) {
    arr[c]++;
  } 

  return arr;
}

