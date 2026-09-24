#include <array>
#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>
#include "huffmanTree.h"
#include "bitReader.h"

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
  root = pq.top();
}

void HuffmanTree::printTree() {
  std::queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    int levelSize = q.size();
    for (int i = 0; i < levelSize; i++) {
      Node* node = q.front();
      std::cout << static_cast<unsigned char>(node->value) << ":";
      std::cout << node->frequency << " ";
      q.pop();

      if (node->left != nullptr) {
        q.push(node->left);
      }
      if (node->right != nullptr) {
        q.push(node->right);
      }
    }
    std::cout << std::endl;
  }
}

void HuffmanTree::buildBits(Node* node, std::string s, std::array<std::string, 256> &path) {
  if (node->left == nullptr && node->right == nullptr) {
    path[node->value] = s;
    return;
  }   
  buildBits(node->left, s + "0", path);
  buildBits(node->right, s + "1", path);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("./fileCompressor <Path>");
    exit(0);
  }
  u_int64_t *arr = readBit(argv[1]);
  std::array<std::string, 256> path;
  HuffmanTree t;
  t.build(arr);
  //t.printTree();
  t.buildBits(t.root, "", path);
  

  free(arr);
  return 0;
}
