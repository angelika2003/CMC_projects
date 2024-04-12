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

template <typename T>

typename T::value_type process(const T &y) {
	if (y.size() == 0) {
		return (typename T::value_type());
	}

	typename T::value_type x;
	typename T::const_iterator i = y.end();

	i--;
	x = *i;//последний элемент
	if (y.size() >= 3) {
		i--;
		i--;
		x += *i;//+3 с конца
	}

	if (y.size() >= 5) {
		i--;
		i--;
		x += *i;//+5 с конца
	}

	return x;
}