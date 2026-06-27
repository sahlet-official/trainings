#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  bool CanEatOnTime(const std::vector<int>& piles, int h, int speed) {
    int needed_hours = 0;
    for (size_t i = 0; i < piles.size(); i++) {
      int pile_size = piles[i];
      needed_hours += (pile_size / speed) + (int)((pile_size % speed) > 0);

      if (needed_hours > h) {
        return false;
      }
    }
    
    return true;
  }

  int MinEatingSpeed(const std::vector<int>& piles, int h) {
    int max_pile = 0;
    int amount_of_piles = 0;
    for (int pile : piles) {
      if (pile < 0) {
        throw std::invalid_argument("piles");
      }

      if (pile > 0) {
        amount_of_piles++;
      }

      max_pile = std::max(max_pile, pile);
    }

    if (amount_of_piles > h) {
      throw std::invalid_argument("amount_of_piles > h");
    }

    int l = 0;
    int r = max_pile;

    while(l < r) {
      int speed = (l + (long long)r) / 2;

      bool can_eat_on_time = CanEatOnTime(piles, h, speed);

      if (!can_eat_on_time) {
        l = speed + 1;
      } else {
        r = speed;
      }
    }

    int min_speed = l;

    return min_speed;
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