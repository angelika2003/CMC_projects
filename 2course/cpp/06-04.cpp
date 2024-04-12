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

template <typename Index, typename Value>//итераторы

Value myremove(Index i_start, Index i_end, Value v_start, Value v_end) {
	Value res_it = v_start;

	int index_of_v = 0;
	int flag = 0;
	for (auto it_v = v_start; it_v != v_end; it_v++) {

		for (auto it_i = i_start; it_i != i_end; it_i++) {
			if (index_of_v == *it_i) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {
			if (it_v != res_it) {
				iter_swap(it_v, res_it);//ненужн и нужн поменяли местами
			}
			res_it++;
		}

		index_of_v++;
		flag = 0;
	}

	return res_it;
}
