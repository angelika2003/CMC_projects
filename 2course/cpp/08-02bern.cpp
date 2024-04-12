#include <iomanip>
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>

using std::vector;
using std::list;
using std::cout;
using std::cin;
using std::endl;

class Result {
public:
    long long int res;
    Result(long long int x) { res = x; }
};
class Returning {};

//some modification of Akkerman function
void func(long long int a, long long int b, unsigned int k) {
    // long long int tmp;
    if (k == 0) {
        throw Result(a + b);
    } else if ((k > 0) && (b == 1)) {
        throw Result(a);
    } else if ((k > 0) && (b > 1)) {
        try {
            func(a, b - 1, k);
        }
        catch (Result &x) {
            func(a, x.res, k - 1);
        }
        catch (Returning &x) {}
    }
    throw Returning();
}

// long long int f(long long int a, long long int b, unsigned int k) {
//     if (k == 0) {
//         return (a + b);
//     } else if ((k > 0) && (b == 1)) {
//         return a;
//     } else if ((k > 0) && (b > 1)) {
//         return f(a, f(a, b - 1, k), k - 1);
//     }
//     return 0;
// }


int main(int argc, char** argv) {
    long long int a, b;
    unsigned int k;

    while (cin >> a >> b >> k) {
        try {
            func(a, b, k);
        }
        catch (Result &x) {
            cout << x.res << endl;
        }
        catch (Returning &x) {}
    }


    // cout << f(2, 2, 2) << endl;
    // cout << f(1, 1, 1) << endl;

    return 0;
}