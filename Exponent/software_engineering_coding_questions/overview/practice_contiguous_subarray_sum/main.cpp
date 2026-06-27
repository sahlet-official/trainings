#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  bool HasGoodSubarray(const std::vector<int>& array, int k) {
    if (array.empty() || k == 0) {
      return false;
    }
    
    const int min_good_subarray_length = 2;

    std::unordered_map</* remainder */ int, /* index */ int> remainderIndicesMap;
    remainderIndicesMap[0] = -1;

    long long prefixSum = 0;
    for(int i = 0; i < array.size(); i++) {
      prefixSum += array[i];
      int remainder = (int)(prefixSum % k);
      
      const auto sameRemainderIter = remainderIndicesMap.find(remainder);

      if (sameRemainderIter == remainderIndicesMap.end()) {
        remainderIndicesMap[remainder] = i;
      } else if (sameRemainderIter->second <= (i - min_good_subarray_length)) {
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
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}