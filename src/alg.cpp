// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

// Определение приоритетов операторов
static int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Проверка, является ли символ оператором
static bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Преобразование инфиксной формы в постфиксную
std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> operators;
    std::string result;
    int i = 0;
    int len = inf.length();

    while (i < len) {
        char c = inf[i];

        // Если цифра - читаем всё число
        if (std::isdigit(c)) {
            while (i < len && std::isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            continue;
        }

        // Если открывающая скобка
        if (c == '(') {
            operators.push(c);
        } else if (c == ')') {  // Если закрывающая скобка
            while (!operators.isEmpty() && operators.top() != '(') {
                result += operators.pop();
                result += ' ';
            }
            if (!operators.isEmpty() && operators.top() == '(') {
                operators.pop();
            }
        } else if (isOperator(c)) {  // Если оператор
            while (!operators.isEmpty() && operators.top() != '(' &&
                   getPriority(operators.top()) >= getPriority(c)) {
                result += operators.pop();
                result += ' ';
            }
            operators.push(c);
        }
        ++i;
    }

    // Выгружаем оставшиеся операторы
    while (!operators.isEmpty()) {
        result += operators.pop();
        result += ' ';
    }

    // Удаляем лишний пробел в конце, если есть
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

// Вычисление выражения, записанного в постфиксной форме
int eval(const std::string& pref) {
    TStack<int, 100> operands;
    int i = 0;
    int len = pref.length();

    while (i < len) {
        char c = pref[i];

        // Если цифра - читаем всё число
        if (std::isdigit(c)) {
            int number = 0;
            while (i < len && std::isdigit(pref[i])) {
                number = number * 10 + (pref[i] - '0');
                ++i;
            }
            operands.push(number);
            continue;
        } else if (isOperator(c)) {  // Если оператор
            if (operands.getSize() >= 2) {
                int b = operands.pop();
                int a = operands.pop();
                int result = 0;

                switch (c) {
                    case '+':
                        result = a + b;
                        break;
                    case '-':
                        result = a - b;
                        break;
                    case '*':
                        result = a * b;
                        break;
                    case '/':
                        result = a / b;
                        break;
                }
                operands.push(result);
            }
        }
        ++i;
    }

    return operands.pop();
}
