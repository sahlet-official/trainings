#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  std::vector<std::vector<int>> MergeIntervals(const std::vector<std::vector<int>>& input_intervals) {
    if (input_intervals.empty()) {
      return {};
    }

    std::vector<std::vector<int>> sorted_intervals(input_intervals.begin(), input_intervals.end());
    std::vector<std::vector<int>> result;

    std::sort(sorted_intervals.begin(), sorted_intervals.end());

    result.push_back(sorted_intervals[0]);

    for (int i = 1; i < sorted_intervals.size(); i++) {
      auto& current_interval = sorted_intervals[i];
      auto& previous_interval = result.back();

      if (current_interval[0] <= previous_interval[1]) {
        previous_interval[1] = std::max(previous_interval[1], current_interval[1]);
      } else {
        result.push_back(current_interval);
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