#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  bool CanFinish(int courses_count, const std::vector<std::vector<int>>& prerequisites) {
    int vertex_count = courses_count;
    std::vector<int> inbounds_count(vertex_count, 0);
    std::vector<std::vector<int>> graph(vertex_count, std::vector<int>());

    for (auto& pair: prerequisites) {
      graph[pair[0]].push_back(pair[1]);
      inbounds_count[pair[1]]++;
    }

    int topological_ordered_vertexes = 0;
    std::queue<int> zero_inbound_vertexes;

    for (int i = 0; i < vertex_count; i++) {
      if (inbounds_count[i] == 0) {
        zero_inbound_vertexes.push(i);
      }
    }

    topological_ordered_vertexes += zero_inbound_vertexes.size();

    while (!zero_inbound_vertexes.empty()) {
      int vertex = zero_inbound_vertexes.front();
      zero_inbound_vertexes.pop();

      for (int child : graph[vertex]) {
        int inbounds = --inbounds_count[child];
        if (inbounds == 0) {
          zero_inbound_vertexes.push(child);
          topological_ordered_vertexes++;
        }
      }
    }
    
    bool graph_has_topological_order = topological_ordered_vertexes == vertex_count;
    bool can_finish_courses = graph_has_topological_order;

    return can_finish_courses;
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