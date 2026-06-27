#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  class MedianFinder {
   public:
    MedianFinder() {}

    void AddNum(int num) {
      if (right_heap_.empty() || num >= right_heap_.top()) {
        right_heap_.push(num);
      } else {
        left_heap_.push(num);
      }

      while (left_heap_.size() > right_heap_.size()) {
        right_heap_.push(left_heap_.top());
        left_heap_.pop();
      }

      while ((left_heap_.size() + 1) < right_heap_.size()) {
        left_heap_.push(right_heap_.top());
        right_heap_.pop();
      }
    }

    double FindMedian() {
      if (right_heap_.empty()) {
        return 0;
      }

      if (left_heap_.size() == right_heap_.size()) {
        double left_median = left_heap_.top();
        double right_median = right_heap_.top();

        double median = (left_median + right_median) / 2;
        return median;
      }

      double median = right_heap_.top();
      return median;
    }
   private:
    
    std::priority_queue<int, std::vector<int>, std::less<int>> left_heap_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right_heap_;
  };

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