#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <sys/types.h>
#include <vector>

struct Node {
  unsigned char value;
  int frequency;
  Node *left;
  Node *right;
};

class HuffmanTree {
private:
  Node *root;

public:
  void build(u_int64_t arr[]);
};

struct Compare {
  bool operator() (Node* a, Node* b) {
    return a->frequency > b->frequency;
  }
};

void HuffmanTree::build(u_int64_t arr[]) {
  std::priority_queue<Node *, std::vector<Node *>, Compare> pq;
  // Insert node into min heap
  for (int i = 0; i < 256; i++) {
    if (arr[i] != 0) {
      Node *n = new Node{static_cast<unsigned char>(i), (int)arr[i], nullptr, nullptr};
      pq.push(n);
    }
  }
  // Build the tree with min heap
  while (pq.size() > 1) {
    Node *n1 = pq.top();
    pq.pop();
    Node *n2 = pq.top();
    pq.pop();
    Node *parent = new Node{'\0', (n1->frequency + n2->frequency), n1, n2};
    pq.push(parent);
  }
}

int main(int argc, char *argv[]) {
  u_int64_t frequency[256]{};
  frequency['A'] = 5;
  frequency['B'] = 9;
  frequency['C'] = 12;
  frequency['D'] = 13;
  frequency['E'] = 16;
  frequency['F'] = 45;

  /*if (argc != 2) {
    printf("./fileCompressor <Path>");
    exit(0);
  }
  std::string path = argv[1];
  std::cout << "Path: " << path;
  */

  HuffmanTree t;
  t.build(frequency);

  return 0;
}
