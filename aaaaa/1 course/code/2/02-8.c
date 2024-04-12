#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);
	int x[n];

	for (int i = 0; i < n; i++) {
		scanf("%d", &x[i]);
	}

	int res = 0;
	int checks;

	for (int i = 1; i < n - 1; i++) {
		if (i <= n / 2) {
			checks = i;
		} else {
			checks = n - i - 1;
		}

		for (int k = 1; k <= checks; k++) {
			if (2 * x[i] == x[i + k] + x[i - k]) {
				res++;
			}
		}
	}

	printf("%d", res);

	return 0;
}
