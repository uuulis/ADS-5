// Copyright 2026 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int getPriority(const char operation) {
  if (operation == '(') return 0;
  if (operation == ')') return 1;
  if (operation == '+' || operation == '-') return 2;
  if (operation == '*' || operation == '/') return 3;
  return -1;
}

std::string infx2pstfx(const std::string& infixExpression) {
  TStack<char, 100> operatorStack;
  std::string postfixExpression;

  for (size_t position = 0; position < infixExpression.length();
       ++position) {
    char currentChar = infixExpression[position];
    if (std::isspace(static_cast<unsigned char>(currentChar))) continue;

    if (std::isdigit(static_cast<unsigned char>(currentChar))) {
      do {
        postfixExpression += infixExpression[position++];
      } while (position < infixExpression.length() &&
               std::isdigit(static_cast<unsigned char>(
                   infixExpression[position])));
      postfixExpression += ' ';
      position--;
    } else if (currentChar == '(') {
      operatorStack.push(currentChar);
    } else if (currentChar == ')') {
      while (!operatorStack.isEmpty() && operatorStack.get() != '(') {
        postfixExpression += operatorStack.get();
        postfixExpression += ' ';
        operatorStack.pop();
      }
      if (!operatorStack.isEmpty()) operatorStack.pop();
    } else {
      int currentPriority = getPriority(currentChar);
      while (!operatorStack.isEmpty() &&
             getPriority(operatorStack.get()) >= currentPriority) {
        postfixExpression += operatorStack.get();
        postfixExpression += ' ';
        operatorStack.pop();
      }
      operatorStack.push(currentChar);
    }
  }

  while (!operatorStack.isEmpty()) {
    postfixExpression += operatorStack.get();
    postfixExpression += ' ';
    operatorStack.pop();
  }

  if (!postfixExpression.empty() && postfixExpression.back() == ' ') {
    postfixExpression.pop_back();
  }
  return postfixExpression;
}

int eval(const std::string& prefixExpression) {
  TStack<int, 100> valueStack;

  for (size_t index = 0; index < prefixExpression.length(); ++index) {
    if (std::isspace(static_cast<unsigned char>(
        prefixExpression[index]))) continue;

    if (std::isdigit(static_cast<unsigned char>(
        prefixExpression[index]))) {
      std::string numberBuffer;
      do {
        numberBuffer += prefixExpression[index++];
      } while (index < prefixExpression.length() &&
               std::isdigit(static_cast<unsigned char>(
                   prefixExpression[index])));
      valueStack.push(std::stoi(numberBuffer));
      index--;
    } else {
      int secondOperand = valueStack.get();
      valueStack.pop();
      int firstOperand = valueStack.get();
      valueStack.pop();

      if (prefixExpression[index] == '+') {
        valueStack.push(firstOperand + secondOperand);
      } else if (prefixExpression[index] == '-') {
        valueStack.push(firstOperand - secondOperand);
      } else if (prefixExpression[index] == '*') {
        valueStack.push(firstOperand * secondOperand);
      } else if (prefixExpression[index] == '/') {
        valueStack.push(firstOperand / secondOperand);
      }
    }
  }
  return valueStack.get();
}
