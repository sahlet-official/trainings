#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  std::vector<int> SortKMessedArray(const std::vector<int>& data, int k) {
    if (k <= 0) {
      return data;
    }

    std::vector<int> arr(data);

    if (k >= data.size()) {
      std::sort(arr.begin(), arr.end());
      return arr;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_hip(arr.begin(), arr.begin() + k + 1);

    for(int i = 0; i < arr.size(); i++) {
      arr[i] = min_hip.top();
      min_hip.pop();

      if (i + k + 1 < arr.size()) {
        min_hip.push(arr[i + k + 1]);
      }
    }

    return arr;
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