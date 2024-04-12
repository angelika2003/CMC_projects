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

//Исключение может также быть сгенерировано из функции, вызванной изнутри блока try:

using namespace std;

class Result {
public:
	long long int res;
	Result(long long int x) {
		res = x;
	}
};

class the_end {};


void func(long long a, long long b, unsigned int k) {

	if (k == 0) {
		//cout << "a+b" << endl;
		throw Result (a + b);
	} else if ((k > 0) && (b == 1)) {
		//cout << "a" << endl;
		throw Result (a);

	} else if ((k > 0) && (b > 1)) {
		try {
			//cout << "f_1" << endl;
			func(a, b - 1, k);
		} catch (Result &x) {
			try {
				//cout << "fffffff" << endl;
				func(a, x.res, k - 1);
			} catch (Result &x) {
				throw Result (x.res);
			} catch (the_end e) {
				//cout << "nooo" << endl;
				throw the_end();
			}
		} catch (the_end e) {
			//cout << "nooo" << endl;
			throw the_end();
		}
	}

	throw the_end();

}


int main() {
	long long a;
	long long b;
	unsigned int k;

	while (cin >> a >> b >> k) {
		try {
			func(a, b, k);
		} catch (Result &x) {
			cout << x.res << endl;
		} catch (the_end e) {
			//cout << "nooo" << endl;
		}
	}

}