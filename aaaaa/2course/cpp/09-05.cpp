#include <iomanip>
#include <iostream>
#include <cstdio>

using namespace std;

bool is_low(const string &s) {
    for (auto i : s) {
        if (!islower(i)) {
            return false;
        }
    }
    return true;
}

int main() {
    string left, right;

    bool kc = true;
    bool kc_lll = true;
    
    bool S_in_right = false;
    bool S_in_left = false;
    bool eps = false;

    while (cin >> left >> right) {
        if (is_low(left)) {
            cout << "-1" << endl;
            return 0;
        }
        if (left.length() != 1) {
            kc = false;
        }

        if (left == "S") {
            S_in_left = true;
        }
        if (right.find('S') != string::npos) {
            S_in_right = true;
        }

        if (left.length() > right.length()) {
            kc_lll = false;
        }
        if ((left != "S") && (right == "_")) {
            kc_lll = false;
        }
        
        if ((left == "S") && (right == "_")) {
            eps = true;
        }
    }




    if (!S_in_left) {
        cout << "-1" << endl;
        return 0;
    }
    if (eps && S_in_right) {
        kc_lll = false;
    }
    if(kc){
        if(kc_lll){
            cout << "23" << endl;
        } else{
            cout << "2" << endl;
        }
        return 0;
    }
    cout << "10" << endl;
}