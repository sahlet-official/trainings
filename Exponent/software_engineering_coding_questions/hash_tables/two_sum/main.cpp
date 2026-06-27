#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  std::vector<int> TwoSum(const std::vector<int>& data, int target) {
    std::unordered_map<int, int> value_index_map;

    for (int i = 0; i < data.size(); i++) {
      const int value = data[i];
      const int another_value = target - value;

      const auto another_value_iter = value_index_map.find(another_value);
      
      if (another_value_iter != value_index_map.end()) {
        const int first_index = another_value_iter->second;
        const int second_index = i;
        return { first_index, second_index };
      }

      value_index_map[value] = i;
    }

    return {};
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