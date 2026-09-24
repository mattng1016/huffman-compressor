#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <array>

#include "bitWriter.h"

void newFile(const char* path, std::array<std::string, 256> &table)  {
  std::string s(path);
  s = s + ".huff";
  const char* p = s.c_str();

  FILE* huffFile = std::fopen(p, "w+b");
  FILE* oldFile = std::fopen(path, "rb");

  int byte, bitCounter = 0; 
  uint8_t buffer = 0;
  while ((byte = fgetc(oldFile)) != EOF) {
    const std::string &code = table[static_cast<unsigned char>(byte)];
    for (auto bit : code) {
      buffer = (buffer << 1) | (bit - '0');
      bitCounter++;
    }
  } 

}

