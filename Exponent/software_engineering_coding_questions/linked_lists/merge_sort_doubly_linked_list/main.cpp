#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  struct Node {
    int val;
    Node* prev;
    Node* next;
  };

  struct List {
    Node* head;
    Node* tail;
  };

  List Merge(List list1, List list2, bool ascending) {
    auto compare = [ascending](int l, int r) -> bool {
      if (ascending) {
        return l < r;
      }

      return l >= r;
    };

    List result;

    if (list2.tail->next == list1.head) {
      std::swap(list1, list2);
    }

    Node* prev_for_head = list1.head->prev;
    Node* next_for_tail = list2.tail->next;

    Node* node1 = list1.head;
    Node* node2 = list2.head;

    if (prev_for_head) prev_for_head->next = nullptr;
    if (next_for_tail) next_for_tail->prev = nullptr;
    list1.head->prev = nullptr;
    list1.tail->next = nullptr;
    list2.head->prev = nullptr;
    list2.tail->next = nullptr;

    auto iterate = [&]() -> Node* {
      Node* node = nullptr;

      if (!node1 && !node2) {
        return nullptr;
      }

      bool first = !node1 ? false : (!node2 ? true : compare(node1->val, node2->val));

      if (first) {
        node = node1;
        node1 = node1->next;
      } else {
        node = node2;
        node2 = node2->next;
      }

      return node;
    };

    result.head = iterate();
    result.tail = result.head;

    result.head->prev = prev_for_head;
    if (prev_for_head) prev_for_head->next = result.head;

    Node* next = iterate();

    while (next) {
      result.tail->next = next;
      next->prev = result.tail;

      result.tail = next;
      next = iterate();
    }

    result.tail->next = next_for_tail;
    if (next_for_tail) next_for_tail->prev = result.tail;

    return result;
  }

  List Sort(Node* head, int length, bool ascending) {
    if (length <= 1) {
      return { head, head };
    }

    int length1 = length / 2;
    int length2 = length - length1;

    List list1 = Sort(head, length1, ascending);
    List list2 = Sort(list1.tail->next, length2, ascending);

    List result_list = Merge(list1, list2, ascending);

    return result_list;
  }

  Node* MergeSortDoublyLinkedList(Node* head, bool ascending) {
    int length = 0;

    for (auto node = head; node;) {
      length++;
      node = node->next;
    }
    

    List list = Sort(head, length, ascending);
    return list.head;
  }

}

namespace tests {
  void Print(const std::string& s) {
    std::cout << s << std::endl;
  }

  void TestSolution1() {
    std::vector<solution_1::Node> vector(3);
    vector[0] = {
      1,
      nullptr,
      &vector[1]
    };
    vector[1] = {
      3,
      &vector[0],
      &vector[2]
    };
    vector[2] = {
      2,
      &vector[1],
      nullptr
    };
    
    auto node = solution_1::MergeSortDoublyLinkedList(&vector[0], true);

    while (node) {
      std::cout << node->val << std::endl;

      node = node->next;
    }
    
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}