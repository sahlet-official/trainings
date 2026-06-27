#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  std::vector<int> SpiralCopy(const std::vector<std::vector<int>>& input_matrix) {
    const int matrix_height = input_matrix.size();
    const int matrix_width = input_matrix.size() ? input_matrix[0].size() : 0;

    std::vector<std::vector<bool>> visited(
      matrix_height,
      std::vector<bool>(matrix_width, false)
    );

    std::vector<int> result;
    result.reserve(matrix_height * matrix_width);

    if (matrix_height * matrix_width == 0) {
      return result;
    }

    int next_x = 0;
    int next_y = 0;

    std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int current_direction = 0;

    auto can_go_further = [&]() {
      return !(
        next_x < 0 || next_x >= matrix_width ||
        next_y < 0 || next_y >= matrix_height ||
        visited[next_y][next_x]
      );
    };

    while (true) {
      if (!can_go_further()) {
        break;
      }

      int cur_x = next_x;
      int cur_y = next_y;

      result.push_back(input_matrix[cur_y][cur_x]);

      visited[cur_y][cur_x] = true;

      next_x = cur_x + directions[current_direction].first;
      next_y = cur_y + directions[current_direction].second;

      if (!can_go_further()) {
        current_direction = (current_direction + 1) % directions.size();
        next_x = cur_x + directions[current_direction].first;
        next_y = cur_y + directions[current_direction].second;
      }
    }

    return result;
  }

}

namespace solution_2 {

  std::vector<int> SpiralCopy(const std::vector<std::vector<int>>& input_matrix) {
    const int matrix_height = input_matrix.size();
    const int matrix_width = input_matrix.size() ? input_matrix[0].size() : 0;

    std::vector<int> result;
    result.reserve(matrix_height * matrix_width);

    if (matrix_height * matrix_width == 0) {
      return result;
    }

    int top_row = 0;
    int right_column = matrix_width - 1;
    int bottom_row = matrix_height - 1;
    int left_column = 0;

    while (top_row <= bottom_row && left_column <= right_column) {
      for (int i = left_column; i <= right_column; i++) {
        result.push_back(input_matrix[top_row][i]);
      }
      top_row++;

      for (int i = top_row; i <= bottom_row; i++) {
        result.push_back(input_matrix[i][right_column]);
      }
      right_column--;

      if (top_row <= bottom_row) {
        for (int i = right_column; i >= left_column; i--) {
          result.push_back(input_matrix[bottom_row][i]);
        }
        bottom_row--;
      }

      if (left_column <= right_column) {
        for (int i = bottom_row; i >= top_row; i--) {
          result.push_back(input_matrix[i][left_column]);
        }
        left_column++;
      }
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