#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  struct ListNode {
    int val;
    ListNode* next;

    ListNode(int val = 0, ListNode* next = nullptr) : val(val), next(next) {}
  };

  ListNode* ReverseList(ListNode* head) {
      ListNode* new_head = nullptr;

      while(head) {
          ListNode* next = head->next;
          head->next = new_head;
          new_head = head;
          head = next;
      }

      return new_head;
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