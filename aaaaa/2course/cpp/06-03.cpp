#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <list>

using namespace std;

template <typename I>

void myapply(I start, I end, function<void(typename iterator_traits<I>::value_type&)> f) {
    for (auto i = start; i != end; i++) {
        f(*i);
    }
}

template <typename I>

vector<reference_wrapper<typename iterator_traits<I>::value_type>> myfilter2(I start, I end, function<bool(typename iterator_traits<I>::value_type&)> f) {
    vector<reference_wrapper<typename iterator_traits<I>::value_type>> v;

    for (auto i = start; i != end; i++) {
        if (f(*i)) {
            v.push_back(*i);
        }
    }

    return v;
}