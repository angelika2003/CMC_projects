#include <stdio.h>
#include <math.h>

const int MAX_MASS = 1e6;

int main(void) {
	int n_digits = 0;
	for (int i = MAX_MASS; i > 0; i /= 3, n_digits++);

	int x;
	scanf("%d", &x);

	int pow_3 = 1, cnt = 0;

	for (int i = 0; i < n_digits; ++i) {	
		int digit = (x / pow_3) % 3;

		if (digit == 1) {
			cnt++;
		} else if (digit == 2) {
			x += pow_3;
			cnt++;
		}

		pow_3 *= 3;
	}

	if (x < MAX_MASS) {
		printf("%d", cnt);
	} else {
		printf("-1");
	}

	return 0;
}