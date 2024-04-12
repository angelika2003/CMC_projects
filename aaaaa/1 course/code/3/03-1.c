#include <stdio.h>

#define N 4

int gcd_for_two(int a, int b) {
	if (a == 0) {
		return b;
	}

	return gcd_for_two(b % a, a);
}

int main(void) {
	int a;
	scanf("%d", &a);

	int b;

	for (int i = 0; i < N - 1; ++i) {
		scanf("%d", &b);
		a = gcd_for_two(a, b);
	}

	printf("%d", a);

	return 0;
}