#include <stdio.h>

#define N 10000

int main(void) {
	int x[N];
	scanf("%d", &x[0]);

	int i = 0;
	while (x[i]) {
		scanf("%d", &x[++i]);
	}

	for (int k = 0; k < i; printf("%d ", x[k]), k += 2);
	for (int k = (i % 2) ? (i - 2) : i - 1; k >= 0; printf("%d ", x[k]), k -= 2);

	return 0;
}