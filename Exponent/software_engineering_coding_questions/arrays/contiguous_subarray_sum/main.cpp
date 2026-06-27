#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  bool HasGoodSubarray(const std::vector<int>& array, int k) {
    if (array.empty() || k == 0) {
      return false;
    }

    const int min_subarray_length = 2;

    std::unordered_map<int /* remainder */, int /* index */> remainders_to_indices;
    remainders_to_indices[0] = -1;

    int prefix_sum_remainder = 0;

    for (int i = 0; i < array.size(); i++) {
      prefix_sum_remainder = (prefix_sum_remainder + array[i]) % k;

      auto iter = remainders_to_indices.find(prefix_sum_remainder);
      if (iter != remainders_to_indices.end()) {
        if (i - iter->second >= min_subarray_length) {
          return true;
        }
      } else {
        remainders_to_indices[prefix_sum_remainder] = i;
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
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}