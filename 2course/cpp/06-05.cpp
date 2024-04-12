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

template <typename iterator>
void selection_sort(iterator start, iterator end) {
	for (iterator i = start; i != end; i++) {
		iterator min = i;

		for (iterator j = i + 1; j != end; j++) {
			if (*j < *min) {
				min = j;
			}
		}
		if (min != i) {
			iter_swap(i, min);
		}
	}
}

template <typename iterator, typename F>
void selection_sort(iterator start, iterator end, F func) {
	for (iterator i = start; i != end; i++) {
		iterator min = i;

		for (iterator j = i + 1; j != end; j++) {
			if (func(*j, *min)) {
				min = j;
			}
		}
		if (min != i) {
			iter_swap(i, min);
		}
	}
}