#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  int FindPeakElement(const std::vector<int>& nums) {
    assert(!nums.empty());

    int l = 0;
    int r = nums.size();

    while (l < r) {
      int m = (l + r) / 2;

      if (nums[m] < nums[m + 1]) {
        l = m + 1;
      } else {
        r = m;
      }
    }
    
    int peak = l;
    return peak;
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