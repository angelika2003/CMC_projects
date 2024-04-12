#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include <string>
#include <set>
#include <utility>
using namespace std;

void check(const string X, string &str, const multimap <string, pair <char, string>> &rulles, set <string> &end_states, int &cnt) {
    if (str.length() == 0) {
        if (end_states.find(X) != end_states.end()) {
            cout << "1\n" << cnt << endl << X << endl;
            exit(0);
        }
        cout << "0\n" << cnt << endl << X << endl;
        exit(0);
    }

    bool flag = true;
    auto range = rulles.equal_range(X);
    for (auto i = range.first; i != range.second; i++) {

        string next_state = i->second.second;
        char edge_symbol = i->second.first;

        if (edge_symbol == str[0]) {
            flag = false;
            cnt++;
            str.erase(0, 1);
            check(next_state, str, rulles, end_states, cnt);
            break;
        }
    }
    if (flag) {
        cout << "0\n" << cnt << endl << X << endl;
        exit(0);
    }
}

int main() {
    string A, B;///STRIINNNNGGGGG
    char a;

    multimap <string, pair <char, string>> rulles;

    string tmp;
    while (getline(cin, tmp) && (tmp != "END")) {
        stringstream sss;
        sss << tmp;
        sss >> A >> a >> B;

        rulles.emplace(A, make_pair(a, B));
    }

    set <string> end_states;
    while ((cin >> tmp) && (tmp != "END")) {
        end_states.insert(tmp);
    }

    string start_state;
    cin >> start_state;

    string str_to_check;
    cin >> str_to_check;

    int cnt = 0;
    check(start_state, str_to_check, rulles, end_states, cnt);
}