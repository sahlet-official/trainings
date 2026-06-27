#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  long long MaxProfitGreedy(const std::vector<int>& stock_prices) {
    long long profit = 0;
    int curent_index = 0;

    while (curent_index + 1 < stock_prices.size()) {
      for (; curent_index + 1 < stock_prices.size(); curent_index++) {
        if (stock_prices[curent_index + 1] > stock_prices[curent_index]) {
          break;
        }
      }

      int local_min = stock_prices[curent_index];

      for (; curent_index + 1 < stock_prices.size(); curent_index++) {
        if (stock_prices[curent_index + 1] < stock_prices[curent_index]) {
          break;
        }
      }

      int local_max = stock_prices[curent_index];

      profit += local_max - local_min;
    }
    
    return profit;
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