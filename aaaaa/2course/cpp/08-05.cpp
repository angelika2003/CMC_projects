#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main() {
    unsigned int sum = 0;

    tm d = {};
    tm cur = {};
    
    cin >> get_time(&d, "%Y-%m-%d");
    system_clock::time_point tp_d = system_clock::from_time_t(mktime(&d));

    while (cin >> get_time(&cur, "%Y-%m-%d")) {
        system_clock::time_point tp_cur = system_clock::from_time_t(mktime(&cur));
        duration<unsigned int, ratio<86400> > diff = duration_cast < duration < unsigned int, ratio < 86400>> > (tp_cur - tp_d);
        sum += abs(static_cast<int>(diff.count()));

        tp_d = tp_cur;
    }

    cout << sum << endl;
}