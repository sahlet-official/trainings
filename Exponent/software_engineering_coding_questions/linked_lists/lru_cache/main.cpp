#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  class LRUCache {
   public:
 
    LRUCache(size_t capacity) : capacity_(capacity) {}

    std::string get(const std::string& key) {
      auto iter = key_to_node_map_.find(key);

      if (iter == key_to_node_map_.end()) {
        return "";
      }

      std::shared_ptr<Node> node = iter->second;

      if (head_ == node) {
        return node->value;
      }

      if (node->prev) {
        node->prev->next = node->next;
      }
      if (node->next) {
        node->next->prev = node->prev;
      }

      node->prev = nullptr;
      node->next = head_;

      head_->prev = node;
      head_ = node;

      return node->value;
    }

    void set(const std::string& key, const std::string& value) {
      if (!this->capacity_) {
        return;
      }

      std::shared_ptr<Node>& node = key_to_node_map_[key];
      if (!node) {
        node = std::make_shared<Node>(key, value);
      } else {
        node->value = value;
      }

      if (!head_) {
        head_ = node;
        tail_ = node;
        return;
      }

      if (head_ == node) {
        return;
      }

      if (node->prev) {
        node->prev->next = node->next;
      }
      if (node->next) {
        node->next->prev = node->prev;
      }

      node->prev = nullptr;
      node->next = head_;

      head_->prev = node;
      head_ = node;

      if (key_to_node_map_.size() > this->capacity_) {
        key_to_node_map_.erase(tail_->key);
        tail_ = std::move(tail_->prev);
      }
    }

   private:
    int capacity_;

    struct Node {
      // TODO: replace key by struct wrapper that can store or only smart pointer to string or only the string
      std::string key;

      std::string value;
      std::shared_ptr<Node> next;
      std::shared_ptr<Node> prev;

      Node(std::string&& key, std::string&& value) : key(key), value(value) {}
    };

    std::unordered_map<std::string, std::shared_ptr<Node>> key_to_node_map_;

    std::shared_ptr<Node> head_;
    std::shared_ptr<Node> tail_;
  };

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