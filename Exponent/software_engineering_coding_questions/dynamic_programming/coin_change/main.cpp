#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  int CoinChange(std::vector<std::vector<int>>* memory_ptr, const std::vector<int>& coins, int amount, int index) {
    if (amount < 0 || index < 0) {
      return -1;
    }

    std::vector<std::vector<int>>& memory = *memory_ptr;
    if (memory[index][amount] != -2) {
      return memory[index][amount];
    }

    if (amount == 0) {
      memory[index][amount] = 0;
      return memory[index][amount];
    }

    int subres1 = CoinChange(memory_ptr, coins, amount, index - 1);
    int subres2 = CoinChange(memory_ptr, coins, amount - coins[index], index);

    int res = 0;

    if (subres2 != -1) {
      if (subres1 != -1) {
        res = std::min(subres1, subres2 + 1);
      } else {
        res = subres2 + 1;
      }
    } else {
      res = subres1;
    }

    memory[index][amount] = res;
    return res;
  }

  int CoinChange(const std::vector<int>& coins, int amount) {
    if (amount < 0) {
      return -1;
    }

    if (coins.empty()) {
      return amount == 0 ? 0 : -1;
    }

    // assert(amount < 10^6)
    // assert(coins.size() < 10^3)

    std::vector<std::vector<int>> memory(coins.size(), std::vector<int>(amount + 1, -2));

    int min_coins_amount = CoinChange(&memory, coins, amount, static_cast<int>(coins.size()) - 1);

    return min_coins_amount;
  } 

}

namespace solution_2 {

  int CoinChange(const std::vector<int>& coins, int amount) {
    if (amount < 0) {
      return -1;
    }

    if (coins.empty()) {
      return amount == 0 ? 0 : -1;
    }

    // assert(amount < INT_MAX)
    // assert(coins.size() < 10^3)

    std::vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 0; i < coins.size(); i++) {
      for (int sum = 0; sum <= amount - coins[i]; sum++) {
        if (dp[sum] == INT_MAX) {
          continue;
        }

        dp[sum + coins[i]] = std::min(dp[sum + coins[i]], dp[sum] + 1);
      }
    }
    

    int min_coins_amount = dp[amount] == INT_MAX ? -1 : dp[amount];

    return min_coins_amount;
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