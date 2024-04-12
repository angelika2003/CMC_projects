#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);
	int x[n + 1];

	for (int i = 0; i < n + 1; i++) {
		x[i] = 0;
	}

	int digit;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &digit);

		if ((digit <= 0) || (digit > n) || (x[digit])) {
			printf("No");
			return 0;
		}

		x[digit] += 1;
	}

	printf("Yes");

	return 0;
}