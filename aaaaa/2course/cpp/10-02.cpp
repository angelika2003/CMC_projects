#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstring>
#include <map>
#include <string>
using namespace std;


void mark_reachable(char X, const multimap <char, string>& rulles, map <char, bool>& reachable) {
    reachable[X] = true;

    auto range = rulles.equal_range(X);
    for(auto i = range.first; i != range.second; i++) {
        for(char c : i->second) {
            if(isupper(c) && !reachable[c]) {//с нетерминал и его еще не проверяли
                mark_reachable(c, rulles, reachable);
            }
        }
    }
}



int main() {
    char X;
    string right_str;
    //X -> right_str

    multimap <char, string> rulles;
    map <char, bool> reachable;

    while (cin >> X >> right_str) {
        rulles.emplace(X, right_str);; //тк multi
        reachable[X] = false;
    }


    mark_reachable('S', rulles, reachable);


    for (auto i : rulles) {
        if (reachable[i.first]){
            cout << i.first << ' ' << i.second << endl;
        }
    }
}