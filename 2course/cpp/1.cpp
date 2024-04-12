#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

class Sum {
    int s;

public:
    Sum(int a, int b) { //конструктор 1
        s = a + b;
    }

    Sum(const Sum & a, int b) { //конструктор 2
        s = a.s + b;
    }

    int get() const{
        return s;
    }

};