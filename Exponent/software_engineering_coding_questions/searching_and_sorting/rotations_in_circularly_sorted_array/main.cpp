#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  int FindRotations(const std::vector<int>& data) {
    if (data.size() <= 1) {
      return 0;
    }

    int l = 0;
    int r = data.size() - 1;

    while (l < r) {
      int m = (l + r) / 2;

      if (data[m] <= data[r]) {
        r = m;
      } else {
        l = m + 1;
      }
    }
    
    return l;
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