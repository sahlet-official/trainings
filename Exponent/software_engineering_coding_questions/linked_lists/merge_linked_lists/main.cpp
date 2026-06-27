#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

  ListNode* Merge(ListNode* head1, ListNode* head2) {
    ListNode head_holder;
    ListNode* tail = &head_holder;

    while (head1 && head2) {
      if (head1->val < head2->val) {
        tail->next = head1;
        head1 = head1->next;
      } else {
        tail->next = head2;
        head2 = head2->next;
      }

      tail = tail->next;
    }

    if (head1) {
      tail->next = head1;
    } else {
      tail->next = head2;
    }

    return head_holder.next;
  }

  ListNode* MergeKLists(const std::vector<ListNode*>& lists, int l, int r) {
    if (l == r) {
      return lists[l];
    }

    int m = (l + r) / 2;

    ListNode* list1 = MergeKLists(lists, l, m);
    ListNode* list2 = MergeKLists(lists, m + 1, r);

    return Merge(list1, list2);
  }

  ListNode* MergeKLists(const std::vector<ListNode*>& lists) {
    if (lists.empty()) {
      return nullptr;
    }

    return MergeKLists(lists, 0, (int)lists.size() - 1);
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