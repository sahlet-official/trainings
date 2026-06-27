#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  void GenerateParentheses(
    std::vector<std::string>* result,
    std::string* variant,
    int n,
    int open_brackets,
    int closed_brackets
  ) {
    if ((open_brackets + closed_brackets) == 2*n) {
      result->push_back(*variant);
      return;
    }

    int char_index = open_brackets + closed_brackets;

    if (open_brackets > closed_brackets) {
      variant->operator[](char_index) = ')';
      GenerateParentheses(
        result,
        variant,
        n,
        open_brackets,
        closed_brackets + 1
      );
    }

    if (open_brackets < n) {
      variant->operator[](char_index) = '(';
      GenerateParentheses(
        result,
        variant,
        n,
        open_brackets + 1,
        closed_brackets
      );
    }
  }

  std::vector<std::string> GenerateParentheses(int n) {
    if (n <= 0) {
      return {};
    }

    std::vector<std::string> result;
    std::string variant(2*n, ' ');

    GenerateParentheses(
      &result,
      &variant,
      n,
      0,
      0
    );

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