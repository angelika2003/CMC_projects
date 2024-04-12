#include <stdio.h>
#include <math.h>

int is_prime(int x) {
	if (x == 1 || x == 0) {
		return 0;
	}

	for (int i = 2; i <= sqrt(x); i++) {
		if ((x % i) == 0) {
			return 0;
		}
	}

	return 1;
}

int main(void) {
	int x;
	scanf("%d", &x);

	while (is_prime(x) == 0) {
		x++;
	}

	printf("%d", x);

	return 0;
}