#include <iomanip>
#include <iostream>
#include <cstdio>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    while (cin >> s) {
        string::iterator i = s.begin();

        while ((*i == '3') || (*i == '4')) {
            i++;
        }

        while ((*i == '1') || (*i == '2')) {
            i++;
        }
        cout << (i == s.end()) << endl;
    }
}