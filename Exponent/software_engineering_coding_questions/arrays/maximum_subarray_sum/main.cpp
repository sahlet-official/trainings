#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  long long MaxSubarraySum(const std::vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }

    long long max_subarray_sum = LONG_LONG_MIN;
    long long min_prefix_sum = 0;
    long long prefix_sum = 0;

    for (int i = 0; i < nums.size(); i++) {
      prefix_sum += nums[i];
      max_subarray_sum = std::max(max_subarray_sum, prefix_sum - min_prefix_sum);
      min_prefix_sum = std::min(min_prefix_sum, prefix_sum);
    }

    return max_subarray_sum;
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