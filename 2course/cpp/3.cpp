#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cin.tie(nullptr);

    int flag = 0;
    int start = 1;
    char c;
    while (cin >> noskipws >> c) {
        if ((c > '0') && (c <= '9')) {
            cout << c;  
            start = 0;
            flag = 0;        
        } else if (c == '0'){
            if (start == 1){
                flag = 1;
            }
            if (flag == 0) {
                cout << c;
            }

        } else {
            if (flag == 1) {
                cout << '0';
            }
            cout << c;

            flag = 0;
            start = 1;
        }
    }

    if (flag == 1) {
        cout << '0';
    }

    return 0;
}