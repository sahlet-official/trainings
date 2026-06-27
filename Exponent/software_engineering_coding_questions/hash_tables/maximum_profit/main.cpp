#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  std::pair<std::string, std::string> MaxProfit(const std::map<std::string, int>& prices) {
    if (prices.empty()) {
      return {"", ""};
    }

    auto min_price_city = &(*prices.begin());
    auto max_price_city = min_price_city;

    for (auto& pair : prices) {
      if (pair.second < min_price_city->second) {
        min_price_city = &pair;
      }

      if (pair.second > max_price_city->second) {
        max_price_city = &pair;
      }
    }

    if (min_price_city->second == max_price_city->second) {
      return {"", ""};
    }

    return {min_price_city->first, max_price_city->first};
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