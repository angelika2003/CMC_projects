#include <iomanip>
#include <cstdio>
#include <iostream>
#include <complex>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

namespace Equations {

template <typename T>
pair < bool, vector < T>> quadratic(const array<T, 3> v) {
	vector <T> roots;
	T c = v[0], b = v[1], a = v[2];

	if (a == T(0)) {
		if (b == T(0)) {
			if (c == T(0)) {
				return make_pair(false, roots);// a=0, b=0, c=0
			} else {
				return make_pair(true, roots);// a=0, b=0, c!=0
			}
		} else {// a=0, b!=0
			roots.push_back(-c / b);
			return make_pair(true, roots);   // a=0, b!=0
		}
	} else {//a!=0
		T d_sqrt = sqrt(b * b - T(4) * a * c);
		T x_1 = (-b + d_sqrt) / (T(2) * a);
		T x_2 = (-b - d_sqrt) / (T(2) * a);

		roots.push_back(x_1);
		roots.push_back(x_2);
		return make_pair(true, roots);
	}
}
}