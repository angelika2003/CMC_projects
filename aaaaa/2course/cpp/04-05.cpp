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

int main() {
	list<int> l;
	int y;
	while ((cin >> y) && (y != 0)) {
		l.push_back(y);
	}

	int cmd1, cmd2;

	list<int> :: iterator i;

	while (cin >> cmd1) {
		i = l.begin();
		if (cmd1 > 0) {
			cin >> cmd2;

			if ((cmd1 - 1 >= 0) && ((size_t)(cmd1 - 1) < l.size())) {
				advance(i, cmd1 - 1);
				i = l.insert(i, cmd2);
			} else {
				l.push_back(cmd2);
			}

		} else if ((-cmd1 - 1 >= 0) && ((size_t)(-cmd1 - 1) < l.size())) {
			advance(i, -cmd1 - 1);
			l.erase(i);
		}
	}

	for (auto i_l : l) {
		cout << i_l << endl;
	}
}