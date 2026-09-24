#include <array>
#include <cstdint>

struct Node {
  unsigned char value;
  int frequency;
  Node *left;
  Node *right;
};

struct Compare {
  bool operator() (Node* a, Node* b) {
    return a->frequency > b->frequency;
  }
};

class HuffmanTree {
public:
  void build(uint64_t arr[]);
  void printTree();
  void buildBits(Node*, std::string, std::array<std::string, 256>&);
  Node *root;
};
