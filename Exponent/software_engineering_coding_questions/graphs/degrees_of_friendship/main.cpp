#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  int FriendDistance(const std::vector<std::vector<int>>& friends, int userA, int userB) {
    if (friends.empty()) {
      return -1;
    }

    if (userA == userB) {
      return 0;
    }
    
    // assert(userA < friends.size());
    // assert(userA >= 0);
    // assert(userB < friends.size());
    // assert(userB >= 0);

    // for (const auto& connections : friends) {
    //   assert(connections.size() == friends.size());
    // }

    std::queue<std::pair<int, int>> queue;
    std::vector<bool> visited(friends.size(), false);
    
    queue.push({userA, 0});
    visited[userA] = true;

    while (!queue.empty()) {
      auto pair = queue.front();
      int current_user = pair.first;
      int distance = pair.second;
      queue.pop();

      if (friends[current_user][userB]) {
        return distance + 1;
      }

      for (int friend_index = 0; friend_index < friends[current_user].size(); friend_index++) {
        if (friends[current_user][friend_index]) {
          if (!visited[friend_index]) {
            queue.push({friend_index, distance + 1});
            visited[friend_index] = true;
          }
        }
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
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}