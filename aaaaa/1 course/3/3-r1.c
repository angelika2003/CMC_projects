#include <stdio.h>

int main(void) {
	int ecx;
	scanf("%d", &ecx);

	int b = 1;
	int a = 0;

	while (ecx > 0) {
		ecx--;
		
		a = a ^ b;
		b = b ^ a;
		a = a ^ b;
		b = a + b;
	}

	printf("%u", (unsigned int)a);

	return 0;
}