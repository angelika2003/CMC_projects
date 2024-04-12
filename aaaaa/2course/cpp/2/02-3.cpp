#include <iostream>

class C {
    int v1;
    int v2;

public:
    C (int a = 0, int b = 0) {
        v1 = a;
        v2 = b;
    }



    C& operator =(const C & s) {

        v1 = s.v1;
        v2 = s.v2;

        return *this;
    }

    int operator ~() const {
        return v1;
    }

    const C operator &() const {
        return *this;
    }

    operator int() const {
        return v1;
    }

    int operator +(const C &v1) const {
        return v1.v1;
    }

    const C operator ++() const {
        return *this;
    }

    int operator *(const C* v1) const {
        return 1;
    }

};

