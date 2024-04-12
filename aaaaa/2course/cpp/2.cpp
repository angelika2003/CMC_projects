#include <iomanip>
#include <iostream>
#include <cstdio>

using namespace std;

class A{
    int a;
    int flag;
public:
    A() {
        flag = 0;
        cin >> a;
    }
    A(const A &x) {
        flag = 1;

        cin >> a;
        a += x.a;
    }

    ~A() {
        if (flag == 1) {
            cout << a << endl;
        }
    }
};