#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

using std::string;
using std::setprecision;

namespace numbers {
class complex {
    double a;
    double b;
public:
    complex(double x = 0, double y = 0) {
        a = x;
        b = y;
    }

    double re() const{
        return a;
    }

    double im() const{
        return b;
    }

    double abs2() const{
        return a * a + b * b;
    }

    double abs() const{
        return sqrt(a * a + b * b);
    }

    explicit complex(const string s) {
        int i = 1;
        int j = 0;
        char s_1[s.length()];
        char s_2[s.length()];

        while (s[i] != ',') {
            s_1[j] = s[i];
            j++;
            i++;
        }

        i++;
        j = 0;

        while (s[i] != ')') {
            s_2[j] = s[i];
            j++;
            i++;
        }

        a = strtod(s_1, NULL);
        b = strtod(s_2, NULL);
    }

    string to_string() const{///////////////////////////////
        std::ostringstream s;
        s << setprecision(10) << "(" << a << "," << b << ")";

        return s.str();
    }

    complex& operator =(const complex & s) {
        if (this == &s) {
            return *this;
        }

        a = s.a;
        b = s.b;
        return *this;
    }

    complex operator +=(const complex & c) {
        a += c.a;
        b += c.b;
        return *this;
    }

    complex operator -=(const complex & c) {
        a -= c.a;
        b -= c.b;
        return *this;
    }

    complex operator *=(const complex & c) {
        double new_a = a * c.a - b * c.b;
        double new_b = a * c.b + b * c.a;
        a = new_a;
        b = new_b;
        return *this;
    }

    complex operator /=(const complex & c) {
        double new_a = (a * c.a + b * c.b) / c.abs2();
        double new_b = (b * c.a - a * c.b ) / c.abs2();
        a = new_a;
        b = new_b;
        return *this;
    }

    complex operator ~() const{/////////////////////////
        return complex(a, -b);
    }

    complex operator -() const{////////////////////////////
        return complex(-a, -b);
    }

    friend complex operator +(const complex &x, const complex &y) {
        complex tmp = x;
        tmp += y;
        return tmp;
    }

    friend complex operator -(const complex &x, const complex &y) {
        complex tmp = x;
        tmp -= y;
        return tmp;
    }

    friend complex operator /(const complex &x, const complex &y) {
        complex tmp = x;
        tmp /= y;
        return tmp;
    }

    friend complex operator *(const complex &x, const complex &y) {
        complex tmp = x;
        tmp *= y;
        return tmp;
    }

};
}