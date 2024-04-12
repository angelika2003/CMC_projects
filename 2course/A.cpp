#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstring>
#include <map>

using namespace std;

int main() {
	int N;
	cin >> N;
	int abc[N];


	for (int i = 0; i < N; i++) {
		cin >> abc[i];
	}

	map <int, int> m;
	for (int i = 0; i < N; i++) {
		cin >> m[abc[i]];
	}

	int text_len;
	cin >> text_len;

	int a;
	int b;
	cin >> a;

	int ans = 0;

	for (int i = 1; i < text_len; i++) {
		cin >> b;

		if (m[a] != m[b]) {
			ans++;
		}

		a = b;
	}

	cout << ans;

}