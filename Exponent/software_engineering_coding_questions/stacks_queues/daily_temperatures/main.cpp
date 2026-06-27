#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  std::vector<int> DailyTemperatures(const std::vector<int>& temperatures) {
    std::vector<int> result(temperatures.size(), 0);
    std::stack<int> nearest_bigger_stack;

    for (int i = (int)temperatures.size() - 1; i >= 0; i--) {
      while (!nearest_bigger_stack.empty()) {
        int top_index = nearest_bigger_stack.top();
        if (temperatures[top_index] <= temperatures[i]) {
          nearest_bigger_stack.pop();
        } else {
          break;
        }
      }

      if (!nearest_bigger_stack.empty()) {
        int nearest_bigger_index = nearest_bigger_stack.top();
        result[i] = nearest_bigger_index - i;
      } /* else {
        result[i] = 0;
      } */

      nearest_bigger_stack.push(i);
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