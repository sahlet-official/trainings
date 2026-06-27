#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  int LeastInterval(const std::vector<char>& tasks, int n) {
    if (tasks.empty() || n < 0) {
      return 0;
    }

    std::vector<int> tasks_count(26, 0);

    for (char task : tasks) {
      tasks_count[task - 'A']++;
    }
    
    std::sort(tasks_count.begin(), tasks_count.end(), std::greater<int>());

    while (tasks_count.back() == 0) {
      tasks_count.pop_back();
    }

    int max_task_frequency = tasks_count[0];

    int tasks_with_max_frequency = 0;

    for(int i = 0; i < tasks_count.size() && tasks_count[i] == max_task_frequency; i++) {
      tasks_with_max_frequency++;
    }

    int space_with_only_one_task_repetition = n + 1;

    int intervals_tasks_with_max_frequency = ((max_task_frequency - 1) * space_with_only_one_task_repetition) + tasks_with_max_frequency;
    int different_tasks_count = tasks_count.size();

    if (different_tasks_count <= n) {
      return intervals_tasks_with_max_frequency;
    } else {
      return std::max(intervals_tasks_with_max_frequency, (int)tasks.size());
    }
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