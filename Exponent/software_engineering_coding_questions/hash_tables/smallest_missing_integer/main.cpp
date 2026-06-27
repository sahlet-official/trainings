#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  size_t SmallestMissingInteger(const std::vector<size_t>& data) {
    std::vector<size_t> nums(data);

    // cyclic sort
    for(size_t i = 0; i < nums.size();) {
      if (nums[i] == i || nums[i] >= nums.size()) {
        i++;
      } else {
        std::swap(nums[i], nums[nums[i]]);
      }
    }

    size_t result = 0;

    for(; result < nums.size(); result++) {
      if (nums[result] != result) {
        break;
      }
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