#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

void process(vector<int64_t>& x, int64_t limit) {
    if (x.size() == 0) {
        return;
    }
    
    vector<int64_t> :: iterator i = x.end() - 1;
    int cnt = 0;
    while (i >= x.begin()) {
        if (*i >= limit) {
            cnt++;
        }
        i--;
    }

    x.reserve(cnt + x.size());
    i = x.end() - 1;

    while (i >= x.begin()) {
        if (*i >= limit) {
            x.emplace_back(*i);
        }
        i--;
    }
}