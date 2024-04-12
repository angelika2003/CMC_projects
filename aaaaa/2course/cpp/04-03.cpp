#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

void process(const vector<int32_t>& n_i, vector<int32_t>& x) {
    if ((n_i.size() == 0) || (x.size() == 0)) {
        return;
    }

    set<int> n_i_set(n_i.begin(), n_i.end());
    int32_t index = 0;

    auto lamda_func = [&index, &n_i_set](int x) {
        return (n_i_set.find(index++) != n_i_set.end());
    };

    auto newEnd = remove_if(x.begin(), x.end(), lamda_func);

    x.erase(newEnd, x.end());
}
