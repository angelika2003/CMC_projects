#include <stdio.h>
#include <stdlib.h>

#define swap(x, y) {int tmp = x; x = y; y = tmp;}

int main(void) {
	int x, y;
	scanf("%d%d", &x, &y);

	x = abs(x);
	y = abs(y);

	if (x < y) {
		swap(x, y);
	}

	int res = 0;

	if ((x + y) % 2 == 1) {
		res++;
		x--;
	}

	res += x * 2;
	printf("%d", res);

	return 0;
}