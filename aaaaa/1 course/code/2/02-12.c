#include <stdio.h>

#define N 8

int main (void) {
	int a[N];
	int b[N];
	int max_a = 0;
	int max_b = 0;

	for (int i = 0; i < N; i++) {
		scanf("%d", &a[i]);
		if (a[i] > max_a) {
			max_a = a[i];
		}
	}

	for (int i = 0; i < N; i++) {
		scanf("%d", &b[i]);
		if (b[i] > max_b) {
			max_b = b[i];
		}
	}

	if (max_a != max_b) {
		printf("-1");
		return 0;
	}
	int res = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (a[i] >= b[N - 1 - j]) {
				res += b[N - 1 - j];
			} else {
				res += a[i];
			}
		}
	}

	printf("%d", res);

	return 0;
}