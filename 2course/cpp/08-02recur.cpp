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


using namespace std;

void func(long long a, long long b, unsigned int k) {

	if (k == 0) {
		cout << a + b << endl;
	} else if ((k > 0) && (b == 1)) {
		cout << a << endl;
	} else if ((k > 0) && (b > 1)) {
		func(a, func(a, b - 1, k), k - 1);
	}


}

int main() {
	long long a;
	long long b;
	unsigned int k;

	cin >> a >> b >> k;
	func(a, b, k);

}