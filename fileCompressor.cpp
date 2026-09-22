#include <iostream>
#include <string>



int main (int argc, char *argv[]) {
  if (argc != 2) {
    printf("./fileCompressor <Path>");
    exit(0);
  } 
  std::string path = argv[1];
  std::cout << "Path: " << path;


  return 0;
}
