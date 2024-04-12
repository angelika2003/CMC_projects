#include <stdio.h>

int F(int x) {
	if (x == 0) {
		return 1;
	}

	return 3*F(x-1);
}

int main(void) {
	unsigned int x;
	scanf("%u", &x);
	printf("%u\n", F(x));
	
	return 0;
}
