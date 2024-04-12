#include <stdio.h>

#define NUMBER 2010

int next_element(int x) {
	int x_tmp = x;
	int pow_10 = 1;

	while (x_tmp > 0) {
		pow_10 *= 10;
		x_tmp /= 10;
	}

	return x * (pow_10 + 1);
}

int main(void) {
	int sequence[NUMBER];

	int N, A;
	scanf("%d%d", &N, &A);

	sequence[0] = N % NUMBER;

	if (sequence[0] == A) {
		printf("YES");
		return 0;
	}

	for (int i = 1; i < NUMBER; i++) {
		sequence[i] = next_element(sequence[i - 1]) % NUMBER;

		if (sequence[i] == A) {
			printf("YES");
			return 0;
		}

		for (int j = 0; j < i; j++) {
			if (sequence[j] == sequence[i]) {
				printf("NO");
				return 0;
			}
		}
	}

	return 0;
}