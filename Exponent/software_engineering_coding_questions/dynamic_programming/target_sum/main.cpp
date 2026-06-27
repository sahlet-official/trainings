#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  long long ChangeSigns(const std::vector<int>& nums, int S) {
    S = std::abs(S);

    long long all_sum = 0;

    for (int i = 0; i < nums.size(); i++) {
      all_sum += nums[i];
    }

    if (
      all_sum < S ||
      (all_sum - S) % 2
    ) {
      return -1;
    }

    long long target_sum = (all_sum - S) / 2;

    std::unordered_map<long long, long long> dp;
    std::unordered_set<long long> new_sums;
    dp[0] = 1;

    for (int num : nums) {
      if (num > target_sum) {
        continue;
      }

      new_sums.insert(num);
      for (const auto& pair : dp) {
        long long new_sum = num + pair.first;
        if (new_sum > target_sum) {
          continue;
        }

        new_sums.insert(new_sum);
      }

      for (long long new_sum : new_sums) {
        dp[new_sum] += dp[new_sum - num];
      }

      new_sums.clear();
    }
    
    return dp[target_sum];
  }

}

namespace solution_2 {

  long long ChangeSigns(const std::vector<int>& nums, int S) {
    S = std::abs(S);

    long long all_sum = 0;

    for (int i = 0; i < nums.size(); i++) {
      all_sum += nums[i];
    }

    if (
      all_sum < S ||
      (all_sum - S) % 2
    ) {
      return -1;
    }

    long long target_sum = (all_sum - S) / 2;

    std::vector<long long> dp(target_sum + 1, 0);
    dp[0] = 1;

    for (int num : nums) {
      for (long long i = target_sum - num; i >= 0; i--) {
        dp[i + num] += dp[i];
      }
    }

    long long result = dp[target_sum] ? dp[target_sum] : -1;
    
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