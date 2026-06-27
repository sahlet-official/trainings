#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  bool IsMatch(
    const std::string &text,
    int text_start_index,
    const std::string &pattern,
    int pattern_start_index
  ) {
    if (pattern.size() <= pattern_start_index) {
      bool match = text.size() <= text_start_index;
      return match;
    }

    if (pattern_start_index + 1 < pattern.size() && pattern[pattern_start_index + 1] == '*') {
      int symbols_skipped = 0;
      while (text_start_index + symbols_skipped <= text.size()) {
        bool match = IsMatch(
          text,
          text_start_index + symbols_skipped,
          pattern,
          pattern_start_index + 2
        );

        if (match) {
          return true;
        }

        if (
          ((text_start_index + symbols_skipped) < text.size()) && 
          (
            pattern[pattern_start_index] == '.' ||
            (pattern[pattern_start_index] == text[text_start_index + symbols_skipped])
          )
        ) {
          symbols_skipped++;
          continue;
        }

        return false;
      }

      return false;
    }

    if (text.size() <= text_start_index) {
      return false;
    }

    if (pattern[pattern_start_index] == '.' || pattern[pattern_start_index] == text[text_start_index]) {
      return IsMatch(
        text,
        text_start_index + 1,
        pattern,
        pattern_start_index + 1
      );
    }

    return false;
  }

  bool IsMatch(const std::string &text, const std::string &pattern) {
    return IsMatch(text, 0, pattern, 0);
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