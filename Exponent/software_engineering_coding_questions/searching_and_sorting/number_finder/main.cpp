#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  int FindFirst(const std::vector<int>& array, int num) {
    if (array.empty()) {
      return -1;
    }

    int l = 0;
    int r = array.size() - 1;

    if (array[l] > num || array[r] < num) {
      return -1;
    }

    if (array[l] == num) {
      return l;
    }

    while (l < r) {
      int m = (l + r) / 2;

      if (array[m] >= num) {
        r = m;
      } else {
        l = m + 1;
      }
    }

    if (array[l] == num) {
      return l;
    }

    return -1;
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