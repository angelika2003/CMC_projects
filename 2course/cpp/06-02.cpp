#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <functional>
#include <list>

using namespace std;

template <typename T> 

T myfilter(const T &x, function<bool(const typename T::value_type&)> f) {
    T res;

    for (auto i = x.begin(); i != x.end(); i++) {
        if (f(*i)) {
            //res.push_back(*i);
            res.insert(res.end(), *i);
        }
    }

    return res;
}