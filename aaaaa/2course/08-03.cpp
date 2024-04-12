#include <iomanip>
#include <iostream>
#include <cstdio>

using namespace std;

class S {
    bool end_flag = false;
    bool first = false;
public:
    int res;

    S(bool x = true) {
        first = x;

        if (cin >> res) {
        } else {
            if (!first) {
                throw 5;
            } else {
                end_flag = true;
            }
        }
    }

    S(const S & x) {
        res = x.res;
        try {
            S tmp(false);
            res += tmp.res;
        }
        catch (int a) {
            end_flag = true;
        }
    }

    ~S() {
        if (end_flag && !first) {
            cout << res << endl;
        }
    }

    explicit operator bool() const { 
        return !end_flag; 
    }

};

void func(S v)
{
    if (v) {
        func(move(v));
    }
}

int main()
{
    func(S());
}