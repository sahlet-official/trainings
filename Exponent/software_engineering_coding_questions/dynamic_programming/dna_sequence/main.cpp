#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  struct StateLinks {
    int A = 0;
    int C = 0;
    int G = 0;
    int T = 0;

    int GetState(char letter) {
      if (letter == 'A') {
        return A;
      } else if (letter == 'C') {
        return C;
      } else if (letter == 'G') {
        return G;
      } else if (letter == 'T') {
        return T;
      } else {
        return -1;
      }
    }

    void SetState(char letter, int state) {
      if (letter == 'A') {
        A = state;
      } else if (letter == 'C') {
        C = state;
      } else if (letter == 'G') {
        G = state;
      } else if (letter == 'T') {
        T = state;
      }
    }
  };

  std::vector<StateLinks> BuildStateMachine(const std::string& gene) {
    std::vector<StateLinks> machine(gene.size() + 1);
    std::vector<char> alphabet = { 'A', 'C', 'G', 'T' };

    if (gene.empty()) {
      return machine;
    }

    machine.front().SetState(gene[0], 1);

    int length_of_suffix = 0;

    for (int i = 1; i < gene.size(); i++) {
      for (char letter : alphabet) {
        int state = machine[length_of_suffix].GetState(letter);
        machine[i].SetState(letter, state);
      }

      machine[i].SetState(gene[i], i + 1);

      length_of_suffix = machine[length_of_suffix].GetState(gene[i]);
    }

    for (char letter : alphabet) {
      int state = machine[length_of_suffix].GetState(letter);
      machine.back().SetState(letter, state);
    }

    return machine;
  }

  int NumOfGeneOccurrences(const std::string& dna, const std::string& gene) {
    if (gene.empty()) {
      return dna.size() + 1;
    }

    auto machine = BuildStateMachine(gene);
    int machine_state = 0;
    
    int gene_count = 0;

    for (int i = 0; i < dna.size(); i++) {
      machine_state = machine[machine_state].GetState(dna[i]);
      if (machine_state == gene.size()) {
        gene_count++;
      }
    }
    
    return gene_count;
  }

}

namespace tests {
  void Print(const std::string& s) {
    std::cout << s << std::endl;
  }

  void TestSolution1() {
    std::cout << solution_1::NumOfGeneOccurrences("ACAC", "AC") << std::endl;
    std::cout << solution_1::NumOfGeneOccurrences("ACAC", "ACAC") << std::endl;

    std::cout << solution_1::NumOfGeneOccurrences("ACCCCA", "CC") << std::endl;
  }

  void TestSolution2() {
  }
}

int main() {
  tests::TestSolution1();
  tests::TestSolution2();

  return 0;
}