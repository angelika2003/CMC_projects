#include <iostream>
#include <iomanip>

#include <algorithm>
#include <map>
#include <string>
#include <cstring>
#include <set>

#include <iomanip>
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <set>

using namespace std;

int main() {
    map<unsigned long long int, map<unsigned long long int, unsigned long long int>> m;

    unsigned long long int x, y, value;
    set<pair<unsigned long long int, unsigned long long int>> dots;


    while (cin >> x) {
        cin >> y >> value;
        if ((x != 0) || (y != 0) || (value != 4294967161)) {


            if ((m.find(x) != m.end()) && (m[x].find(y) != m[x].end())) {

                m[x][y] += value;
                m[x][y] %= 4294967161;

            } else {
                m[x][y] = value;
                dots.insert({x, y});
            }
        }
    }

    for (auto i : dots) {
        if (m[i.first][i.second] != 0) {
            cout << i.first << ' ' << i.second << ' ' << m[i.first][i.second] << endl;
        }

    }
}