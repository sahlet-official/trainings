#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  long long MaxContainer(const std::vector<int>& heights) {
    if (heights.size() < 2) {
      return 0;
    }

    long long max_container = 0;

    int l = 0;
    int r = heights.size() - 1;

    while (l < r) {
      int min_height = std::min(heights[l], heights[r]);

      long long cur_container = (long long)(r - l) * min_height;
      max_container = std::max(max_container, cur_container);

      if (heights[l] == min_height) {
        l++;
      }

      if (heights[r] == min_height) {
        r--;
      }
    }

    return max_container;
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