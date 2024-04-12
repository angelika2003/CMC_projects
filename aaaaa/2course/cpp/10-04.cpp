#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

// Функция, которая возвращает приоритет для заданной операции
int getPriority(char op) {
    static unordered_map<char, int> priorities = {
        {'*', 1},
        {'/', 1},
        {'+', 2},
        {'-', 2},
        {'&', 3},
        {'^', 4},
        {'|', 5}
    };
    return priorities[op];
}

int main() {
    string expression;
    getline(cin, expression);

    stack<char> st;
    bool error = false;
    for (char ch : expression) {
        if (islower(ch)) { // переменная
            if (!st.empty() && st.top() == '(') {
                st.push(ch); // если на вершине стека скобка, то все ок
            } else {
                // если на вершине стека операция или переменная, то проверим приоритет
                while (!st.empty() && !error && getPriority(ch) >= getPriority(st.top())) {
                    st.pop(); // выполним операции на вершине стека, если приоритет выше
                    if (st.empty() || st.top() != '(') {
                        error = true; // если стек опустел или не обнаружена открывающая скобка, значит есть лишние скобки
                    }
                }
                st.push(ch);
            }
        } else if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            if (st.empty() || st.top() == '(') {
                error = true; // если на вершине стека скобка, то ошибка - есть лишняя закрывающая скобка
            } else {
                st.pop(); // удаляем соответствующую открывающую скобку
                while (!st.empty() && !error && !islower(st.top())) {
                    // если на вершине стека операция, то выполним ее
                    st.pop();
                    if (st.empty() || st.top() == '(') {
                        error = true; // если стек опустел или на вершине осталась скобка, значит есть лишние скобки
                    }
                }
            }
        }
    }

    if (!st.empty() || error) {
        cout << "Error: Invalid expression!" << endl;
    } else {
        cout << expression << endl;
    }

    return 0;
}