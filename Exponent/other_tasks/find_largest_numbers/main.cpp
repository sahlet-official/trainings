#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <queue>

namespace test_cases {
  struct TestCase {
    std::vector<int> data;
    int m;
  };

  const TestCase kTestCase1 = {{}, 1};
  const TestCase kTestCase2 = {{1}, 0};
  const TestCase kTestCase3 = {{1}, 3};
  const TestCase kTestCase4 = {{1,5,4,2,3}, 3};
}

namespace solution_1 {

  std::vector<int> GetMaximums(const std::vector<int>& data, int maximums_count) {
    if (maximums_count > data.size()) {
      throw "unexpected input data";
    }

    if (maximums_count <= 0) {
      return {};
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap(
      data.begin(),
      data.begin() + maximums_count
    );

    for(int i = maximums_count; i < data.size(); i++) {
      if (min_heap.top() < data[i]) {
        min_heap.pop();
        min_heap.push(data[i]);
      }
    }

    std::vector<int> result;
    result.reserve(maximums_count);

    while (!min_heap.empty()) {
      result.push_back(min_heap.top());
      min_heap.pop();
    }

    return result;
  }

}

namespace tests {
  void PrintVector(const std::vector<int>& vector) {
    for(const auto& element : vector) {
      std::cout << element << ' ';
    }

    std::cout << std::endl;
  }

  void TestSolution1() {
    // PrintVector(solution_1::GetMaximums(test_cases::kTestCase1.data, test_cases::kTestCase1.m));
    PrintVector(solution_1::GetMaximums(test_cases::kTestCase2.data, test_cases::kTestCase2.m));
    // PrintVector(solution_1::GetMaximums(test_cases::kTestCase3.data, test_cases::kTestCase3.m));
    PrintVector(solution_1::GetMaximums(test_cases::kTestCase4.data, test_cases::kTestCase4.m));
  }
}

int main() {
  tests::TestSolution1();

  return 0;
}