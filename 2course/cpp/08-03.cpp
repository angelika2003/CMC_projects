#include <iomanip>
#include <cstdio>
#include <iostream>

using namespace std;

class S {
    bool end_flag = false;
    bool is_first = false;
public:
    int sum;

    S(bool x = true) {
        is_first = x;

        if (cin >> sum) {
        } else {
            if (!is_first) {
                throw 5;
            } else {
                end_flag = true;
            }
        }
    }

    S(const S & x) {
        sum = x.sum;
        try {
            S tmp(false);
            sum += tmp.sum;
        }
        catch (int a) {
            end_flag = true;
        }
    }

    ~S() {
        if (end_flag && !is_first) {
            cout << sum << endl;
        }
    }

    operator bool() const { 
        return !end_flag; 
    }

};

// void func(S v)
// {
//     if (v) {
//         func(move(v));
//     }
// }

// int main()
// {
//     func(S());
// }