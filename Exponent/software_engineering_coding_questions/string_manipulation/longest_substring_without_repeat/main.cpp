#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  int LongestSubstringWithoutRepeat(const std::string& s) {
    if (s.empty()) {
      return 0;
    }

    std::unordered_set<char> char_set;

    int l = 0;
    int r = 1;
    int max_substring_length = 1;

    char_set.insert(s[0]);

    while (r < s.size()) {
      while (char_set.count(s[r])) {
        char_set.erase(s[l]);
        l++;
      }

      char_set.insert(s[r]);
      r++;

      int cur_substring_length = r - l;

      max_substring_length = std::max(max_substring_length, cur_substring_length);
    }

    return max_substring_length;
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