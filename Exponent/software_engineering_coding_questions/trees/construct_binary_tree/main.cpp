#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  struct TreeNode {
    int val;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  };

  std::shared_ptr<TreeNode> ConstructBinaryTree(
    const std::vector<int>& preorder,
    const std::vector<int>& inorder,
    std::unordered_map<int, int>* vertex_to_inorder_indices_map,
    int* preorder_root_index,
    int inorder_left_bound,
    int inorder_right_bound
  ) {
    if (inorder_left_bound > inorder_right_bound) {
      return nullptr;
    }

    int root_vertex = preorder[*preorder_root_index];
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(root_vertex);

    int inorder_root_index = (*vertex_to_inorder_indices_map)[root_vertex];

    (*preorder_root_index)++;

    std::shared_ptr<TreeNode> left = ConstructBinaryTree(
      preorder,
      inorder,
      vertex_to_inorder_indices_map,
      preorder_root_index,
      inorder_left_bound,
      inorder_root_index - 1
    );
    std::shared_ptr<TreeNode> right = ConstructBinaryTree(
      preorder,
      inorder,
      vertex_to_inorder_indices_map,
      preorder_root_index,
      inorder_root_index + 1,
      inorder_right_bound
    );

    root->left = left;
    root->right = right;

    return root;
  }

  std::shared_ptr<TreeNode> ConstructBinaryTree(
    const std::vector<int>& preorder,
    const std::vector<int>& inorder
  ) {
    if (preorder.size() != inorder.size()) {
      return nullptr;
    }

    // assert(all elements in preorder are distinct)
    // assert(all elements in inorder are distinct)
    // assert(all elements in preorder exists in inorder)

    std::unordered_map<int, int> vertex_to_inorder_indices_map;

    for (int i = 0; i < inorder.size(); i++) {
      int vertex = inorder[i];
      vertex_to_inorder_indices_map[vertex] = i;
    }

    int preorder_root_index = 0;

    return ConstructBinaryTree(
      preorder,
      inorder,
      &vertex_to_inorder_indices_map,
      &preorder_root_index,
      0,
      (int)inorder.size() - 1
    );
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