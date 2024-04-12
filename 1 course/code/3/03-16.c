#include <stdio.h>
#include <math.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int max(int x, int y) {
	if (x >= y) {
		return x;
	}
	return y;
}

int pow2(int a, int b, int mod) {
	if ((a == 1) || (b == 0)) {
		return 1;
	}

	if (b == 1) {
		return a;
	}

	if (b % 2 == 0) {
		int c = pow2(a, b / 2, mod);
		return (c * c) % mod ;
	}

	return (a * pow2(a, b - 1, mod)) % mod;
}

int pow3(int a, int b, int c, int mod) {
	return pow2(a % mod, pow(b, c), mod);
}

int max_pow(int a, int b, int c, int mod) {
	int max_pow = 0;

	for (int i = 0; i < 3; i++) {
		max_pow = max(max_pow, pow3(a, b, c, mod));
		swap(&b, &c);

		max_pow = max(max_pow, pow3(a, b, c, mod));
		swap(&a, &b);
	}

	return max_pow;
}

int main(void) {
	int a, b, c, mod;
	scanf("%d%d%d%d", &a, &b, &c, &mod);

	printf("%d", max_pow(a, b, c, mod));

	return 0;
}