#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    cin >> noskipws;
    char cur = 0, old = 0;
    int cnt = 1;

    if(!(cin >> old)){
        return 0;
    }

    while (cin >> cur) {

        if (old == cur) {
            cnt++;
            old = cur;
        } else {
            if (old == '#') {
                cout << "##" << hex << cnt << "#";
            } else {
                if (cnt <= 4) {
                    for (int i = 0; i < cnt; i++) {
                        cout << old;
                    }
                } else {
                    cout << "#" << old << hex << cnt << "#";
                }
            }

            old = cur;
            cnt = 1;
        }
    }

    if (old == '#') {
        cout << "##" << hex << cnt << "#";
    } else {
        if (cnt <= 4) {
            for (int i = 0; i < cnt; i++) {
                cout << old;
            }
        } else {
            cout << "#" << old << hex << cnt << "#";
        }
    }
    
    return 0;
}