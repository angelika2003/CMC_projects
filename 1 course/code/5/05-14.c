#include <stdio.h>
#include <math.h>

int end_digit[4] = {1, 3, 7, 9};

int is_prime(int x) {
	for (int div = 2; div <= sqrt(x) ; ++div) {
		if (x % div == 0) {
			return 0;
		}
	}

	return 1;
}

void super_prime(int number, int num_digits, int cur_n_digits) {
	if (num_digits == cur_n_digits) {
		printf("%d ", number);
		return;
	}

	for (int i = 0; i < 4; ++i) {
		int longer_num = number * 10 + end_digit[i];
		if (is_prime(longer_num)) {
			super_prime(longer_num, num_digits, cur_n_digits + 1);
		}
	}
}

int main(void) {
	int N;
	scanf("%d", &N);

	int begin_digit[4] = {2, 3, 5, 7};
	for (int i = 0; i < 4; ++i) {
		super_prime(begin_digit[i], N, 1);
	}

	return 0;
}