#include <iostream>
#include <iomanip>

#include <algorithm>
#include <vector>

using namespace std;

unsigned int num_bits(unsigned int n) {
	unsigned int count = 0;
	while (n) {
		count += n & 1;
		n >>= 1;
	}
	return count;
}




int main() {
	vector<unsigned int> v;
	unsigned int x;
	while (cin >> x) {
		v.push_back(x);
	}

	auto lamda_cmp = [](const unsigned int &a, const unsigned int &b) {
		return (num_bits(a) < num_bits(b));
	};

	stable_sort(v.begin(), v.end(), lamda_cmp);

	for (auto i : v) {
		cout << i << endl;
	}
}
