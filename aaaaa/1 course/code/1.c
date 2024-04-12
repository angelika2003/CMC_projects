#include <stdio.h>

float pow1(int x, int a) {
	if (a < 0) {
		return 1 / pow1(x, -a);
	}
	if (a == 0) {
		return 1;
	}
	if (a == 1) {
		return x;
	}

	if (a % 2 == 0) {
		int c = pow1(x, a / 2);
		return c * c;
	}

	return x * pow1(x, a - 1);
}



int main(void) {
	int a, b;
	scanf("%d %d", &a, &b);

	printf("%f", pow1(a, b));

	return 0;
}