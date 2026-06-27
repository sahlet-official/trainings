#include <iostream>
#include <bits/stdc++.h>

namespace test_cases {
  struct TestCase {
    std::string data;
    size_t k;
  };

  const TestCase kTestCase1 = { "acqqwwwqqcce", 3 };
  const TestCase kTestCase2 = { "awe", 2 };
  const TestCase kTestCase3 = { "awwae", 2 };
  const TestCase kTestCase4 = { "eawwae", 2 };
  const TestCase kTestCase5 = { "aaaaawwae", 2 };
  const TestCase kTestCase6 = { "awe", 1 };
  const TestCase kTestCase7 = { "", 2 };
  const TestCase kTestCase8 = { "qwee", 0 };
  const TestCase kTestCase9 = { "qwee", 10 };
}

namespace solution_1 {

  struct Node {
    size_t index = 0;
    Node* pointer_to_prev_different = nullptr;
    Node* pointer_to_next = nullptr;
    int number_in_duplicate_sequence = 1;
  };

  std::string RemoveDuplicates(const std::string& data, size_t k) {
    if (data.size() < k) {
      return data;
    }

    if (data.size() == 0) {
      return "";
    }

    if (k == 1 || k == 0) {
      return "";
    }

    Node empty_first_node;
    std::vector<Node> nodes(data.size());
    Node* previous = &empty_first_node;

    empty_first_node.pointer_to_next = &nodes[0];

    size_t removed_characters_amount = 0;

    for (size_t i = 0; i < data.size(); i++) {
      nodes[i].index = i;

      if (previous != &empty_first_node && data[i] == data[previous->index]) {
        nodes[i].pointer_to_prev_different = previous->pointer_to_prev_different;
        if  (i+1 < data.size()) {
          nodes[i].pointer_to_next = &nodes[i+1];
        }
        nodes[i].number_in_duplicate_sequence = previous->number_in_duplicate_sequence + 1;
        if (nodes[i].number_in_duplicate_sequence == k) {
          // remove duplicates
          nodes[i].pointer_to_prev_different->pointer_to_next = nodes[i].pointer_to_next;
          previous = nodes[i].pointer_to_prev_different;
          removed_characters_amount += k;
        } else {
          previous = &nodes[i];
        }
      } else {
        nodes[i].pointer_to_prev_different = previous;
        if  (i+1 < data.size()) {
          nodes[i].pointer_to_next = &nodes[i+1];
        }
        previous = &nodes[i];
      }
    }

    std::string result;
    result.reserve(data.size() - removed_characters_amount);

    {
      Node* current_node_ptr = empty_first_node.pointer_to_next;
      while (current_node_ptr) {
        char curent_character = data[current_node_ptr->index];
        result.push_back(curent_character);
        current_node_ptr = current_node_ptr->pointer_to_next;
      }
    }

    return result;
  }

}

namespace solution_2 {

  std::string RemoveDuplicates(const std::string& data, size_t k) {
    if (k == 0) {
      return "";
    }

    std::vector<std::pair<char, size_t>> stack;

    for (size_t i = 0; i < data.size(); i++) {
      if (stack.empty() || stack.back().first != data[i]) {
        stack.push_back({data[i], 1});
      } else {
        stack.back().second++;
        if (stack.back().second == k) {
          stack.pop_back();
        }
      }
    }
    

    std::string result;

    for (size_t i = 0; i < stack.size(); i++) {
      result.append(stack[i].second, stack[i].first);
    }
    

    return result;
  }

}

namespace tests {
  void Print(const std::string& s) {
    std::cout << s << std::endl;
  }

  void TestSolution1() {
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase1.data, test_cases::kTestCase1.k));
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase2.data, test_cases::kTestCase2.k));
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase3.data, test_cases::kTestCase3.k));
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase4.data, test_cases::kTestCase4.k));
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase5.data, test_cases::kTestCase5.k));
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase6.data, test_cases::kTestCase6.k));
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase7.data, test_cases::kTestCase7.k));
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase8.data, test_cases::kTestCase8.k));
    Print(solution_1::RemoveDuplicates(test_cases::kTestCase9.data, test_cases::kTestCase9.k));
  }

  void TestSolution2() {
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase1.data, test_cases::kTestCase1.k));
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase2.data, test_cases::kTestCase2.k));
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase3.data, test_cases::kTestCase3.k));
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase4.data, test_cases::kTestCase4.k));
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase5.data, test_cases::kTestCase5.k));
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase6.data, test_cases::kTestCase6.k));
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase7.data, test_cases::kTestCase7.k));
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase8.data, test_cases::kTestCase8.k));
    Print(solution_2::RemoveDuplicates(test_cases::kTestCase9.data, test_cases::kTestCase9.k));
  }
}

int main() {
  // tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}