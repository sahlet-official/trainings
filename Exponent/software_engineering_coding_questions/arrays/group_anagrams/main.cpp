#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
}

namespace solution_1 {

  typedef std::string StringRepresentation;

  StringRepresentation BuildStringRepresentation(const std::string& s) {
    std::vector<int> count(26, 0);

    for (char ch : s) {
      count[ch - 'a']++;
    }

    std::stringstream ss;
    for (int i = 0; i < count.size(); ++i) {
      ss << count[i] << "#";
    }

    return ss.str();
  }

  std::vector<std::vector<std::string>> GroupAnagrams(const std::vector<std::string>& strs) {
    std::unordered_map<StringRepresentation, std::vector<std::string>> anagram_groups;

    std::vector<std::vector<std::string>> result;

    for (int i = 0; i < strs.size(); i++) {
      const auto string_representation = BuildStringRepresentation(strs[i]);
      anagram_groups[string_representation].push_back(strs[i]);
    }

    for (auto& pair : anagram_groups) {
      result.push_back(std::move(pair.second));
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