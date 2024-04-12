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
#include <cassert>

//S -> aSd | aKd
//K -> bKc | bc

using namespace std;

void f(int n, int k){
    if (n == 0) {
    	return;
    }

    int m = (k - 2 * n) / 2;

    string cur = string(n, 'a') + string(m, 'b') + string(m, 'c') + string(n, 'd');
    cout << cur << endl;

    f(n - 1, k);
}

int main(){
    int k; 
    cin >> k;
    if (k % 2 == 0) {
    	f((k - 2) / 2, k);
    }
}