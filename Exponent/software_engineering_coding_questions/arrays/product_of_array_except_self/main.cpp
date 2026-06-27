#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  std::vector<int> ProductExceptSelf(const std::vector<int>& nums) {
    std::vector<int> result(nums.size(), 0);

    int zeros_count = 0;
    long long all_product = 1;
    int zero_index = -1;

    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == 0) {
        zeros_count++;
        zero_index = i;
      } else {
        all_product *= nums[i];
      }
    }

    if (zeros_count >= 2) {
      return result;
    }

    if (zeros_count == 1) {
      result[zero_index] = all_product;
      return result;
    }

    for (int i = 0; i < nums.size(); i++) {
      result[i] = all_product / nums[i];
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