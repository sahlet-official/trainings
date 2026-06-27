#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;
  };

  Node* FindInOrderSuccessor(Node *input_node) {
    if (!input_node) {
      return nullptr;
    }

    if (input_node->right) {
      Node* node = input_node->right;

      while (node->left) {
        node = node->left;
      }

      return node;
    }

    Node* parent = input_node->parent;

    while (parent && parent->key < input_node->key) {
      parent = parent->parent;
    }

    return parent;
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