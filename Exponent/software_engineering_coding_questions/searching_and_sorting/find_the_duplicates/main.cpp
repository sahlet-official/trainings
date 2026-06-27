#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  std::vector<int> FindDuplicatesLinear(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    std::vector<int> result;

    size_t i = 0;
    size_t j = 0;
    while (i < arr1.size() && j < arr2.size()) {
      if (arr1[i] == arr2[j]) {
        if (result.empty() || result.back() != arr1[i]) {
          result.push_back(arr1[i]);
        }

        i++;
        j++;
      } else if (arr1[i] < arr2[j]) {
        i++;
      } else if (arr1[i] > arr2[j]) {
        j++;
      }
    }

    return result;
  }

  std::vector<int> FindDuplicatesFast(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    std::vector<int> result;

    auto left_bound = arr2.begin();

    for (size_t i = 0; i < arr1.size(); i++) {
      if (!result.empty() && result.back() == arr1[i]) {
        continue;
      }

      left_bound = std::lower_bound(left_bound, arr2.end(), arr1[i]);

      if (left_bound == arr2.end()) {
        break;
      }

      if (*left_bound == arr1[i]) {
        result.push_back(arr1[i]);
      }
    }

    return result;
  }

  std::vector<int> FindDuplicates(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    if (arr1.empty() || arr2.empty()) {
      return {};
    }

    auto arr1_ptr = &arr1;
    auto arr2_ptr = &arr2;

    if (arr1_ptr->size() > arr2_ptr->size()) {
      std::swap(arr1_ptr, arr2_ptr);
    }

    auto& smaller_arr = *arr1_ptr;
    auto& bigger_arr = *arr2_ptr;

    bool linear_approach = (smaller_arr.size() + bigger_arr.size()) <= smaller_arr.size() * std::ceil(std::log2(bigger_arr.size()));

    if (linear_approach) {
      return FindDuplicatesLinear(smaller_arr, bigger_arr);
    }

    return FindDuplicatesFast(smaller_arr, bigger_arr);
  }

}

namespace tests {
  void Print(const std::string& s) {
    std::cout << s << std::endl;
  }

  void TestSolution1() {
    solution_1::FindDuplicates({1}, {1});
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}