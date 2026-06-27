#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  bool CanPartition(const std::vector<int>& nums) {
    long long all_sum = 0;
    for (int num : nums) {
      all_sum += num;
    }

    if (all_sum % 2) {
      return false;
    }

    long long target = all_sum / 2;

    std::vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums) {
      for (long long i = target - num; i >= 0; i--) {
        dp[i + num] = dp[i + num] || dp[i];
      }

      if (dp[target]) {
        return true;
      }
    }

    return false;
  }
}

namespace tests {
  void Print(const std::string& s) {
    std::cout << s << std::endl;
  }

  void TestSolution1() {
    std::cout << solution_1::CoinChange({1, 2, 5}, 11) << std::endl;
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}