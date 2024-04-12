#include <iostream>
using namespace std;

bool is_correct(char* s, int len);
bool is_valid_char(char c);

int main() {
    const int MAX_LEN = 1000000; // максимальный размер массива
    char* s = new char[MAX_LEN];
    int len = 0;
    bool flag_is_str = false;
    bool flag_last_char = false; // флаг последнего символа
    while (char c = getchar()) {
        if (is_valid_char(c)) {
            if (flag_last_char == false) { // если это первый символ новой строки
                flag_is_str = true; // обнуляем флаг, тк новая строка
                len = 0;
                if (c == '0' || c == '1') {
                    s[len++] = c;
                }
            } else { // если это не первый символ новой строки
                if (flag_is_str == true) {
                    if (len == MAX_LEN) {
                        cerr << "Input string is too long" << endl;
                        return 1;
                    }
                    s[len++] = c;
                }
            }
            flag_last_char = true;
        } else { // если символ не является цифрой и не пробельным
            flag_last_char = false;
            if (flag_is_str == true) {
                cout << is_correct(s, len) << endl;
                flag_is_str = false;
            }
        }
    }
    // обработка последней считанной строки
    if (flag_is_str == true) {
        cout << is_correct(s, len) << endl;
    }
    delete[] s;
}

bool is_valid_char(char c) {
    return c == '0' || c == '1' || c == ' ' || c == '\n';
}

bool is_correct(char* s, int len) {
    bool is_normal = false;
    int state = 0; // Начальное состояние
    for (int i = 0; i < len; i++) {
        char c = s[i];
        switch (state) { // Переходы между состояниями
        case 0:
            if (c == '0') state = 1;
            else if (c == '1') is_normal = false;
            else return false;
            break;
        case 1:
            if (c == '0') state = 1;
            else if (c == '1') state = 2;
            else return false;
            break;
        case 2:
            if (c == '0') is_normal = true, state = 3;
            else return false;
            break;
        case 3:
            if (c == '0') state = 4;
            else return false;
            break;
        case 4:
            if (c == '0') state = 5;
            else return false;
            break;
        case 5:
            if (c == '1') state = 2;
            else return false;
            break;
        }
    }
    return is_normal;
}