#include <iostream>
#include <iomanip>

#include <algorithm>
#include <map>

using namespace std;

class mark {
public:
    long double sum;
    unsigned long long int cnt;
};

int main() {

    map <string, mark> m;
    string name;


    while (cin >> name) {
        if (m.find(name) == m.end()) {
            // not found
            mark a;
            a.cnt = 1;
            cin >> a.sum;
            m[name] = a;
        } else {
            // found
            int x;
            cin >> x;
            m[name].sum += x;
            m[name].cnt++;
        }

    }

    for (auto x : m) {
        long double ans = x.second.sum / x.second.cnt;
        cout << x.first << ' ' << ans << endl;
    }

}