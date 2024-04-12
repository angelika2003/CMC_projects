#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;
	int a[N];
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	vector <pair <int, int>> v;
	int ans_1, ans_2;
	double sum_1 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (a[j] - a[i] > 0) {
				v.push_back({i, j});
				if (a[j] / a[i] > sum_1) {
					ans_1 = i;
					ans_2 = j;
					sum_1 = a[j] / a[i];
				}
			}
		}
	}

	if (v.size() == 0) {
		cout << "0";
		return 0;
	}

	double cur_sum;
	double max_sum = sum_1;

	int ans_i1, ans_i2;
	int ans_j1, ans_j2;
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (v[j].first > v[i].second) {
				cur_sum = a[v[i].second] * a[v[j].second] / a[v[j].first] / a[v[i].first];

				if (cur_sum > max_sum) {
					ans_i1 = v[i].first;
					ans_i2 = v[i].second;

					ans_j1 = v[j].first;
					ans_j2 = v[j].second;

					max_sum = cur_sum;
				}

			}
		}
	}

	if (max_sum == sum_1) {
		cout << "1" << endl;
		cout << ans_1 + 1 << " " << ans_2 + 1;
		return 0;
	}

	cout << "2" << endl;
	cout << ans_i1  + 1 << " " << ans_i2 + 1 << endl;
	cout << ans_j1 + 1 << " " << ans_j2 + 1;
}