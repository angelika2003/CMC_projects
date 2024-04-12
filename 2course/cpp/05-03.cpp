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

class Date {
public:
    string str;

    Date(const string& tmp) {
        string year = tmp.substr(0, 4);
        string mon;
        string day;

        if (tmp[6] == '/') {
            mon = tmp.substr(5, 1);
            day = tmp.substr(7, 10);
        } else {
            mon = tmp.substr(5, 2);
            day = tmp.substr(8, 10);
        }

        ostringstream new_string;
        new_string << year << "/" << setfill('0') << setw(2) << mon << "/" << setfill('0') << setw(2) << day;

        str = new_string.str();
    }

};

int main() {
    map <string, map<string, int>> m;

    set<string> names;
    set<string> dates;

    string name;
    string data;
    int x;

    while (cin >> name) {
        cin >> data >> x;
        Date a(data);
        m[name][a.str] = x;
        dates.insert(a.str);
        names.insert(name);
    }

    cout << ". ";
    for (auto d : dates) {
        cout << d << ' ';
    }

    cout << endl;

    for (auto i : names) {
        cout << i<< " ";
        for (auto d : dates) {
            if (m[i].find(d) != m[i].end()) {
                cout << m[i][d] << " ";
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
}