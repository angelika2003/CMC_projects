#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int cmp (pair <long long, long long> i, pair <long long, long long>j)
{
	return i.second < j.second;
}

int main() {
	long long N, ideal, time;
	cin >> N >> ideal >> time;

	vector <pair <long long, long long>> l;
	for (int i = 0; i < N; i++) {
		long long cur;
		cin >> cur;
		l.push_back({i + 1, abs(cur - ideal)});
	}
//сортировка листа из пар
	sort(l.begin(), l.end(), cmp);

	long long ans = 0;
	vector <long long> ans_ind;
	for (int i = 0; i < N; i++) {
		if (time - l[i].second >= 0) {
			time -= l[i].second;
			ans_ind.push_back(l[i].first);
			ans++;
		} else {
			break;
		}
	}

	cout << ans << endl;

	for (int i = 0; i < ans; i++) {
		cout << ans_ind[i] << " ";
	}

}