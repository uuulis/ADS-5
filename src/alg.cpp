// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <sstream>
#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string out;
    size_t i = 0;
    while (i < inf.length()) {
        char c = inf[i];
        if (std::isdigit(c)) {
            // собираем многозначное число
            std::string num;
            while (i < inf.length() && std::isdigit(inf[i])) {
                num += inf[i];
                ++i;
            }
            out += num + ' ';
            continue; // i уже увеличено
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.getTop() != '(') {
                out += stack.pop();
                out += ' ';
            }
            if (!stack.isEmpty() && stack.getTop() == '(') {
                stack.pop(); // удаляем '('
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && priority(stack.getTop()) >= priority(c) && stack.getTop() != '(') {
                out += stack.pop();
                out += ' ';
            }
            stack.push(c);
        }
        // пропускаем пробелы во входной строке (если есть)
        ++i;
    }
    while (!stack.isEmpty()) {
        out += stack.pop();
        out += ' ';
    }
    return out;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;
    while (iss >> token) {
        if (std::isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else {
            int right = stack.pop();
            int left = stack.pop();
            int result = 0;
            switch (token[0]) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/': result = left / right; break;
            }
            stack.push(result);
        }
    }
    return stack.pop();
}
