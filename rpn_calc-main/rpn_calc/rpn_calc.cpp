#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

class RPNCalculator {
private:
  std::stack<double> stack;

public:
  void push(double value) { stack.push(value); }

  double pop() {
    if (stack.empty()) {
      throw std::runtime_error("错误: 栈为空");
    }
    double value = stack.top();
    stack.pop();
    return value;
  }

  void clear() {
    while (!stack.empty())
      stack.pop();
    std::cout << "栈已清空。\n";
  }

  void showStack() {
    std::stack<double> temp = stack;
    std::cout << "[栈] ";
    if (temp.empty()) {
      std::cout << "(空)\n";
      return;
    }
    while (!temp.empty()) {
      std::cout << temp.top() << " ";
      temp.pop();
    }
    std::cout << "\n";
  }

  void calculate(const std::string &token) {
    if (token == "+") {
      binaryOp(std::plus<double>());
    } else if (token == "-") {
      binaryOp(std::minus<double>());
    } else if (token == "*") {
      binaryOp(std::multiplies<double>());
    } else if (token == "/") {
      if (stack.size() < 2)
        throw std::runtime_error("错误: 操作数不足");
      double b = pop();
      if (b == 0)
        throw std::runtime_error("错误: 除零错误");
      double a = pop();
      push(a / b);
    } else if (token == "?") { // 就当开根了
      if (stack.empty())
        throw std::runtime_error("错误: 栈为空");
      double a = pop();
      if (a < 0)
        throw std::runtime_error("错误: 不能对负数开平方");
      push(std::sqrt(a));
    } else if (token == "^") { // 次方
      if (stack.size() < 2)
        throw std::runtime_error("错误: 操作数不足");
      double b = pop(); // 指数
      double a = pop(); // 底数
      push(std::pow(a, b));
    }

    else {
      try {
        push(std::stod(token));
      } catch (...) {
        throw std::runtime_error("错误: 无效输入 '" + token + "'");
      }
    }
  }
  template <typename Op> void binaryOp(Op op) {
    if (stack.size() < 2)
      throw std::runtime_error("错误: 操作数不足");
    double b = pop();
    double a = pop();
    push(op(a, b));
  }
};

int main() {
  RPNCalculator calc;
  std::string line;

  std::cout << "====================== ###RPN### ====================\n";
  std::cout << "q<Enter> quit\n";
  std::cout << "c<Enter> clear\n";
  std::cout << "+ - * / ^ ?\n\n";

  while (true) {
    std::cout << ">>> ";
    if (!std::getline(std::cin, line))
      break;
    if (line == "q")
      break;
    if (line == "c") {
      calc.clear();
      continue;
    }
    if (line == "s") {
      calc.showStack();
      continue;
    }

    std::istringstream iss(line);
    std::string token;
    try {
      while (iss >> token) {
        calc.calculate(token);
      }
      calc.showStack();
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
    }
  }

  std::cout << "程序结束。\n";
  return 0;
}
