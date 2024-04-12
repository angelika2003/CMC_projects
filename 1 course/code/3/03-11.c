#include <stdio.h>

int gcd(int a, int b) {
	if (a == 0) {
		return b;
	}

	return gcd(b % a, a);
}

void fractions_sum(int num, int a, int b) {
	for (int n = num; n > 0; n-- ) {
		int a_i, b_i;
		scanf("%d%d", &a_i, &b_i);

		a = a * b_i + a_i * b;
		b = b * b_i;
	}
	
	int int_part = a / b;
	a = a % b;
	int div = gcd(a, b);
	printf("%d %d %d", int_part, a / div, b / div);		
}

int main(void) {
	int n, a_1, b_1;
	scanf("%d%d%d", &n, &a_1, &b_1);

	fractions_sum(n - 1, a_1, b_1);

	return 0;
}