#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  std::vector<std::string> ModifyString(const std::string& source, const std::string& target) {
    std::vector<std::pair<int, int>> parent_directions = {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}};
    const char no_parent = 0;
    const char upper_parent = 1;
    const char left_parent = 2;
    const char diagonal_parent = 3;

    struct Cell {
      int cost = 0;
      char parent = no_parent;
    };

    std::vector<std::vector<Cell>> matrix(
      source.size() + 1,
      std::vector<Cell>(target.size() + 1)
    );

    for (int i = 1; i <= target.size(); i++) {
      matrix[0][i].cost = i;
      matrix[0][i].parent = left_parent;
    }

    for (int i = 1; i <= source.size(); i++) {
      matrix[i][0].cost = i;
      matrix[i][0].parent = upper_parent;
    }

    for (int i = 1; i <= source.size(); i++) {
      for (int j = 1; j <= target.size(); j++) {
        int from_upper_cost = matrix[i-1][j].cost + 1;
        int from_diagonal_cost = matrix[i-1][j-1].cost + (static_cast<int>(source[i - 1] != target[j - 1]) * 2);
        int from_left_cost = matrix[i][j-1].cost + 1;

        char parent = left_parent;
        int cost = from_left_cost;

        if (from_diagonal_cost < cost) {
          parent = diagonal_parent;
          cost = from_diagonal_cost;
        }

        if (from_upper_cost < cost) {
          parent = upper_parent;
          cost = from_upper_cost;
        }

        matrix[i][j].cost = cost;
        matrix[i][j].parent = parent;
      }
    }

    std::vector<std::string> result;

    char parent = matrix.back().back().parent;
    int i = matrix.size() - 1;
    int j = matrix.front().size() - 1;

    while (parent != no_parent) {
      if (parent == diagonal_parent) {
        std::string step = std::string(1, target[j-1]);
        result.push_back(step);
        i--;
        j--;
      } else if (parent == upper_parent) {
        std::string step = "-" + std::string(1, source[i-1]);
        result.push_back(step);
        i--;
      } else if (parent == left_parent) {
        std::string step = "+" + std::string(1, target[j-1]);
        result.push_back(step);
        j--;
      }

      parent = matrix[i][j].parent;
    }

    std::reverse(result.begin(), result.end());
    
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