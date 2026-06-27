#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  long long TrapRainWater(const std::vector<int>& bars) {
    std::vector<int> water_level(bars.size(), INT_MIN);

    int max_left = INT_MIN;
    for (int i = 0; i < bars.size(); i++) {
      max_left = std::max(max_left, bars[i]);
      water_level[i] = max_left;
    }
    
    int max_right = INT_MIN;
    for (int i = (int)bars.size() - 1; i >= 0; i--) {
      max_right = std::max(max_right, bars[i]);
      water_level[i] = std::min(max_right, water_level[i]);
    }

    long long all_water_amount = 0;

    for (int i = 0; i < bars.size(); i++) {
      all_water_amount += std::max(0, water_level[i] - bars[i]);
    }

    return all_water_amount;  
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