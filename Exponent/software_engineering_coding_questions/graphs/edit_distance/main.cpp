#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  int CountDistance(const std::string& word_1, const std::string& word_2) {
    int distance = 0;
    for (int i = 0; i < word_1.size(); i++) {
      if (word_1[i] != word_2[i]) {
        distance++;
      }
    }

    return distance;
  }

  bool DistanceIsOne(const std::string& word_1, const std::string& word_2) {
    int distance = 0;
    for (int i = 0; i < word_1.size(); i++) {
      if (word_1[i] != word_2[i]) {
        distance++;
        if (distance > 1) {
          return false;
        }
      }
    }

    return distance == 1;
  }

  int FindEditDistance(const std::vector<std::string>& dictionary, const std::string& start_word, const std::string& end_word) {
    // assert(no same words in 'dictionary')
    // assert(all words length are same)
    // assert(we cant delete ot insert letters into words)

    int start_word_index = -1;
    int end_word_index = -1;

    std::unordered_set<int> not_visited;

    for (int i = 0; i < dictionary.size(); i++) {
      not_visited.insert(i);
      if (dictionary[i] == start_word) {
        start_word_index = i;
      }
      if (dictionary[i] == end_word) {
        end_word_index = i;
      }
    }

    if (start_word_index < 0 || end_word_index < 0) {
      return -1;
    }

    if (start_word == end_word) {
      return 0;
    }

    struct QueueElement {
      int distance = 0;
      int heuristic = 0;
      int vertex = -1;

      bool operator>(const QueueElement& another) const {
        return (this->distance + this->heuristic) > (another.distance + another.heuristic);
      }
    };

    std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> priority_queue;

    priority_queue.push({
      0,
      CountDistance(dictionary[start_word_index], dictionary[end_word_index]),
      start_word_index
    });
    not_visited.erase(start_word_index);

    while (!priority_queue.empty()) {
      QueueElement curent_element = priority_queue.top();
      priority_queue.pop();

      if (curent_element.vertex == end_word_index) {
        return curent_element.distance;
      }

      std::vector<int> neighbors;
      for (int vertex : not_visited) {
        if (DistanceIsOne(dictionary[curent_element.vertex], dictionary[vertex])) {
          neighbors.push_back(vertex);
        }
      }

      for (int vertex : neighbors) {
        not_visited.erase(vertex);
        priority_queue.push({
          curent_element.distance + 1,
          CountDistance(dictionary[vertex], dictionary[end_word_index]),
          vertex
        });
      }
    }

    return -1;
  }

}

namespace tests {
  void Print(const std::string& s) {
    std::cout << s << std::endl;
  }

  void TestSolution1() {
    std::vector<std::string> dictionary = {"hit", "hot", "dot", "dog", "cog"};
    std::string word_1 = "hit";
    std::string word_2 = "cog";

    std::cout << solution_1::FindEditDistance(dictionary, word_1, word_2) << std::endl;
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}