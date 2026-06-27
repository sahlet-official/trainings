#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  std::vector<int> FindDifference(const std::vector<int>& arr_1, const std::vector<int>& arr_2) {
    std::vector<int> result;

    std::unordered_map<int, bool> resulting_arr_1_elements;
    std::unordered_set<int> resulting_arr_2_elements;

    for(int elem : arr_1) {
      resulting_arr_1_elements[elem] = true;
    }

    for(int elem : arr_2) {
      auto iter = resulting_arr_1_elements.find(elem);
      if (iter == resulting_arr_1_elements.end()) {
        resulting_arr_2_elements.insert(elem);
      } else {
        iter->second = false;
      }
    }

    for (auto& pair : resulting_arr_1_elements) {
      if (pair.second) {
        result.push_back(pair.first);
      }
    }

    for (int elem : resulting_arr_2_elements) {
      result.push_back(elem);
    }

    return result;
  }

}

namespace solution_2 {

  std::vector<int> FindDifference(const std::vector<int>& arr_1, const std::vector<int>& arr_2) {
    std::vector<int> result;

    std::unordered_set<int> set_1(arr_1.begin(), arr_1.end());
    std::unordered_set<int> set_2(arr_2.begin(), arr_2.end());

    for (int elem: set_1) {
      if (!set_2.count(elem)) {
        result.push_back(elem);
      }
    }

    for (int elem: set_2) {
      if (!set_1.count(elem)) {
        result.push_back(elem);
      }
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