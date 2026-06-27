#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  class UnionHelper {
   public:
    void Connect(int v, int u) {
      int v_parent = this->FindParent(v);
      int u_parent = this->FindParent(u);

      if (v_parent == u_parent) {
        return;
      }

      int& v_parent_rank = unions_[v_parent];
      int& u_parent_rank = unions_[u_parent];

      if (v_parent_rank > u_parent_rank) {
        v_parent_rank = u_parent;
      } else if (v_parent_rank < u_parent_rank) {
        u_parent_rank = v_parent;
      } else {
        u_parent_rank = v_parent;
        v_parent_rank--;
      }
    }

    bool IsConnected(int v, int u) {
      int v_parent = this->FindParent(v);
      int u_parent = this->FindParent(u);

      if (v_parent == u_parent) {
        return true;
      }

      return false;
    }

    void Add(int v) {
      unions_[v] = -1;
    }

    int CountComponents() const {
      int components_count = 0;

      for (auto& pair : unions_) {
        if (pair.second < 0) {
          components_count++;
        }
      }

      return components_count;
    }

   private:

    int FindParent(int v) {
      int parent = unions_[v];
      if (parent == 0) {
        unions_[v] = -1;
      } else if (parent > 0) {
        int parent_of_parent = this->FindParent(parent);
        unions_[v] = parent_of_parent;
        return parent_of_parent;
      }

      return v;
    }
    
    std::unordered_map<int, int /*rank or parent*/> unions_;
  };

  int GetNumberOfIslands(const std::vector<std::vector<int>>& binary_matrix) {
    // asset(matrix is rectangular and every row has same length)

    UnionHelper union_helper;

    for (int i = 0; i < binary_matrix.size(); i++) {
      for (int j = 0; j < binary_matrix[i].size(); j++) {
        if (binary_matrix[i][j] != 1) {
          continue;
        }

        union_helper.Add(i * binary_matrix[i].size() + j);

        if (i > 0 && binary_matrix[i-1][j] == 1) {
          union_helper.Connect(i * binary_matrix[i].size() + j, (i - 1) * binary_matrix[i].size() + j);
        }

        if (j > 0 && binary_matrix[i][j-1] == 1) {
          union_helper.Connect(i * binary_matrix[i].size() + j, i * binary_matrix[i].size() + (j - 1));
        }
      }
    }

    int islands_count = union_helper.CountComponents();
    return islands_count;
  }

}

namespace tests {
  void Print(const std::string& s) {
    std::cout << s << std::endl;
  }

  void TestSolution1() {
    solution_1::AreSentencesSimilar({"i", "love", "coding"}, {"i", "adore", "coding"}, {{"love", "adore"}});
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}