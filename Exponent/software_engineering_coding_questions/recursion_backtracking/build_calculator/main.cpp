#include <iostream>
#include <bits/stdc++.h>

namespace solution_1 {

  class Expresion {
   public:
    virtual double execute() = 0;
  };

  class Number : Expresion {
   public:
    Number(double number) : number_(number) {}
    
    virtual double execute() override {
      return number_;
    }

   private:
    double number_;
  };

  enum class Operator : int {
    kMinus = 0,
    kPlus = 1,
    kMultiplication = 2,
    kDivision = 3,
  };

  class Operation : Expresion {
   public:
    Operation(
      Operator oper,
      std::unique_ptr<Expresion> left,
      std::unique_ptr<Expresion> right
    ) :
    oper_(oper),
    left_(std::move(left)),
    right_(std::move(right))
    {}
    
    virtual double execute() override {
      double left_value = left_->execute();
      double right_value = right_->execute();

      if (oper_ == Operator::kMinus) {
        return left_value - right_value;
      }

      if (oper_ == Operator::kPlus) {
        return left_value + right_value;
      }

      if (oper_ == Operator::kDivision) {
        return left_value / right_value;
      }

      if (oper_ == Operator::kMultiplication) {
        return left_value * right_value;
      }
    }

   private:
    Operator oper_;
    std::unique_ptr<Expresion> left_;
    std::unique_ptr<Expresion> right_;
  };
  
  bool IsDigit(char ch) {
    return ch >= '0' && ch <= '9';
  }

  bool IsSpace(char ch) {
    return ch == ' ';
  }

  double calc(const std::string& expr) {
    std::stringstream stringstream(expr);

    

    while (!stringstream.eof()) {
      char ch = static_cast<char>(stringstream.peek());

      if (IsSpace(ch)) {
        stringstream >> ch;
        continue;
      }

      if (IsDigit(ch)) {
        double number = 0;
        stringstream >> number;
        continue;
      }
    }
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