#include <iostream>
#include <iomanip>

#include <algorithm>
#include <map>
#include <string>
#include <cstring>
#include <set>

#include <iomanip>
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <set>

using namespace std;

int main() {
	map<unsigned long long int, map<unsigned long long int, unsigned long long int>> m;
	map<unsigned long long int, map<unsigned long long int, unsigned long long int>> res;

	uint32_t x, y;
	unsigned long long int value;
	set<pair<unsigned long long int, unsigned long long int>> dots;

	map <uint32_t, vector<uint32_t>> list_for_y;

	while (cin >> x) {
		cin >> y >> value;
		if ((x == 0) && (y == 0) && (value == 4294967161)) {
			break;
		}

		m[x][y] = value;
		list_for_y[y].push_back(x);
	}

	while (cin >> x) {
		cin >> y >> value;

		for (auto i : list_for_y[x]) {
			if ((res.find(i) != res.end()) && (res[i].find(y) != res[i].end())) {
				res[i][y] += ((value * m[i][x]) % 4294967161);
				res[i][y] %= 4294967161;
			} else {
				res[i][y] = (value * m[i][x]) % 4294967161;
				dots.insert({i, y});
			}
		}
	}


	for (auto i : dots) {
		if (res[i.first][i.second] != 0) {
			cout << i.first << ' ' << i.second << ' ' << res[i.first][i.second] << endl;
		}

	}
}