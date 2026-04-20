// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include "tstack.h"

int priority(char op) {
    static const std::map<char, int> prio = {
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}
    };
    auto it = prio.find(op);
    return (it != prio.end()) ? it->second : 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;
    size_t i = 0;
    while (i < inf.length()) {
        char c = inf[i];
        if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            continue;
        } else if (c == '(') {
            stack.push(c);
            ++i;
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            if (!stack.isEmpty() && stack.top() == '(') {
                stack.pop();
            }
            ++i;
        } else if (isOperator(c)) {
            while (!stack.isEmpty() && stack.top() != '(' &&
                   priority(stack.top()) >= priority(c)) {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            stack.push(c);
            ++i;
        } else {
            ++i;
        }
    }
    while (!stack.isEmpty()) {
        result += stack.top();
        result += ' ';
        stack.pop();
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;
    while (iss >> token) {
        if (token.length() == 1 && isOperator(token[0])) {
            int right = stack.top(); stack.pop();
            int left  = stack.top(); stack.pop();
            int res = 0;
            switch (token[0]) {
                case '+': res = left + right; break;
                case '-': res = left - right; break;
                case '*': res = left * right; break;
                case '/': res = left / right; break;
            }
            stack.push(res);
        } else {
            stack.push(std::stoi(token));
        }
    }
    return stack.isEmpty() ? 0 : stack.top();
}
