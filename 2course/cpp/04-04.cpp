#include <cstdio>
#include <iomanip> 
#include <cstring>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

struct Sum
{
	void operator()(double n) { sum += n; }
	double sum{0};
};

int main() {
	vector<double> v;
	double x;
	while (cin >> x) {
		v.push_back(x);
	}


	int n = v.size() / 10;
	vector<double> :: iterator start = v.begin();
	v.erase(start, start + n);
	vector<double> :: iterator end = v.end();
	v.erase(end - n, end);

	sort(v.begin(), v.end());

	int new_n = v.size() / 10;
	start = v.begin();
	v.erase(start, start + new_n);
	end = v.end();
	v.erase(end - new_n, end);


	Sum s = for_each(v.begin(), v.end(), Sum());

	s.sum /= v.size();

	cout << fixed << setprecision(10) << s.sum;
}
