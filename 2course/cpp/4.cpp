#include <iostream>
#include <cstdio>
#include <math.h>
#include <iomanip>

using namespace std;

int main() {
    long double sum = 0.0, sumsq = 0.0;

    long double x;
    int cnt = 0;

    while (cin >> x) {
        sum += x;
        sumsq += x * x;
        cnt++;
    }
    long double mid = sum / cnt;
    long double ans = sumsq / cnt - mid * mid;
    cout << fixed << setprecision(10) << mid << endl << sqrt(ans) << endl;

    return 0;
}