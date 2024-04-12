#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

void process(const vector<uint64_t>& x, vector<uint64_t>& y, int offset) {
    if (y.size() == 0) {
        return;
    }

    vector<uint64_t> :: const_iterator i = x.begin();
    vector<uint64_t> :: iterator j = y.end() - 1;

    while ((i < x.end()) && (j >= y.begin())) {
        *j += *i;
        j--;
        i += offset;
    }
}
