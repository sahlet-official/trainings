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

  bool AreSentencesSimilar(const std::vector<std::string>& sentence_1,
                            const std::vector<std::string>& sentence_2,
                            const std::vector<std::pair<std::string, std::string>>& similar_pairs) {
    if (sentence_1.size() != sentence_2.size()) {
      return false;
    }
    
    std::unordered_map<std::string, int> string_to_vertex;
    int vertex_number = 0;
    UnionHelper union_helper;

    for (auto& pair: similar_pairs) {
      int& vertex_1 = string_to_vertex[pair.first];
      if (vertex_1 == 0) {
        vertex_1 = ++vertex_number;
      }

      int& vertex_2 = string_to_vertex[pair.second];
      if (vertex_2 == 0) {
        vertex_2 = ++vertex_number;
      }

      union_helper.Connect(vertex_1, vertex_2);
    }

    for (int i = 0; i < sentence_1.size(); i++) {
      if (sentence_1[i] == sentence_2[i]) {
        continue;
      }

      int vertex_1 = string_to_vertex[sentence_1[i]];
      int vertex_2 = string_to_vertex[sentence_2[i]];

      if (vertex_1 == 0 || vertex_2 == 0) {
        return false;
      }

      bool is_connected = union_helper.IsConnected(vertex_1, vertex_2);

      if (!is_connected) {
        return false;
      }
    }

    return true;
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