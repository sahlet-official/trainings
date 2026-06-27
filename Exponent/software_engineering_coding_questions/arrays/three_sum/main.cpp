#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  std::vector<std::vector<int>> ThreeSum(const std::vector<int>& data) {
    int target = 0;
    std::vector<int> array = data;
    std::vector<std::vector<int>> result;

    std::sort(array.begin(), array.end());

    for (int i = 0; i < array.size(); i++) {
      if (i > 0 && array[i] == array[i - 1]) {
        continue;
      }

      int two_sum = target - array[i];

      int l = i + 1;
      int r = (int)array.size() - 1;
      while (l < r) {
        if ((array[l] + array[r]) > two_sum) {
          r--;
        } else if ((array[l] + array[r]) < two_sum) {
          l++;
        } else {
          std::vector<int> triplet = { array[i], array[l], array[r] };
          result.push_back(triplet);
          l++;
          r--;

          while (l < r) {
            bool moved = false;
            if (array[l] == array[l - 1]) {
              l++;
              moved = true;
            }

            if (array[r] == array[r + 1]) {
              r--;
              moved = true;
            }

            if (!moved) {
              break;
            }
          }
        }
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
    solution_1::ThreeSum({-1, 0, 1, 2, -1, -4});
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}