#include <stdio.h>

#define N 10000

int main(void) {
	int x[N];
	scanf("%d", &x[0]);

	int i = 0;
	while (x[i]) {
		scanf("%d", &x[++i]);
	}

	i--;

	while (i >= 0) {
		printf("%d ", x[i]);
		i--;
	}

	return 0;
}