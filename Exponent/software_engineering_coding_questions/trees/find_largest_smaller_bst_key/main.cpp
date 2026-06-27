#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;
  };

  int FindLargestSmallerKey(Node *root_node, int num) {
    auto node = root_node;

    int result = -1;

    while (true) {
      if (!node) {
        return result;
      }

      if (node->key >= num) {
        node = node->left;
        continue;
      }

      result = node->key;
      node = node->right;
    }

    return result;
  }

}

namespace tests {
  void Print(const std::string& s) {
    std::cout << s << std::endl;
  }

  void TestSolution1() {
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}