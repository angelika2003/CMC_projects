#include <stdio.h>

int main(void) {
	unsigned int x1;
	scanf("%u", &x1);

	unsigned int x = (x1 ^ (x1 - 1)) + 1;

	int cf = 0;
	if (x == 0) {
		cf = 1;
	}

	x = ((x >> 1) & 0x7fffffff) + cf * 0x80000000;

	printf("%u\n", x);

	return 0;
}