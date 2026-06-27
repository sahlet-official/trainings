#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
  const std::vector<int> kTestCase1 = {};
  const std::vector<int> kTestCase2 = { 0, 0, 0, 0 };
  const std::vector<int> kTestCase3 = { 1, 0, 1 };
  const std::vector<int> kTestCase4 = { 0, 1, 0, 1, 0, 1, 0, 1, 0 };
  const std::vector<int> kTestCase5 = { 1, 2, 3, 4 };
}

namespace solution_1 {

  std::vector<int> MoveZerosToEnd(const std::vector<int>& input_array) {
    std::vector<int> result(input_array.size(), 0);
    size_t result_index = 0;
    
    for (size_t i = 0; i < input_array.size(); i++) {
      if (input_array[i] != 0) {
        result[result_index] = input_array[i];
        result_index++;
      }
    }

    return result;
  }

}

namespace solution_2 {

  void MoveZerosToEnd(std::vector<int>* array_ptr) {
    auto& array = *array_ptr;

    const auto first_zero_iter = std::find(array.begin(), array.end(), 0);
    const size_t first_zero_index = first_zero_iter - array.begin();

    size_t left_index = first_zero_index;
    size_t right_index = first_zero_index;

    for (; right_index < array.size();) {
      if (array[right_index] != 0) {
        std::swap(array[left_index], array[right_index]);
        left_index++;
      }
      right_index++;
    }

    return;
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
    PrintVector(solution_1::MoveZerosToEnd(test_cases::kTestCase1));
    PrintVector(solution_1::MoveZerosToEnd(test_cases::kTestCase2));
    PrintVector(solution_1::MoveZerosToEnd(test_cases::kTestCase3));
    PrintVector(solution_1::MoveZerosToEnd(test_cases::kTestCase4));
    PrintVector(solution_1::MoveZerosToEnd(test_cases::kTestCase5));
  }

  void TestSolution2() {
    std::vector<int> test_case;

    test_case = test_cases::kTestCase1;
    solution_2::MoveZerosToEnd(&test_case);
    PrintVector(test_case);

    test_case = test_cases::kTestCase2;
    solution_2::MoveZerosToEnd(&test_case);
    PrintVector(test_case);

    test_case = test_cases::kTestCase3;
    solution_2::MoveZerosToEnd(&test_case);
    PrintVector(test_case);

    test_case = test_cases::kTestCase4;
    solution_2::MoveZerosToEnd(&test_case);
    PrintVector(test_case);

    test_case = test_cases::kTestCase5;
    solution_2::MoveZerosToEnd(&test_case);
    PrintVector(test_case);
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}