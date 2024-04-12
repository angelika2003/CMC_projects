#include <stdio.h>

#define NUMBER_TO_INT 48
#define LETTER_TO_INT 96
#define MAX 8


int main(void) {
	int x[MAX+2][MAX+2] = {};
	char s[2*MAX*MAX];
	scanf("%s", s);

	for (int k = 0; s[k] != '\0'; k += 2) {
		int a = s[k] - LETTER_TO_INT - 1;
		int b = s[k + 1] - NUMBER_TO_INT - 1;
		for (int i = a; i < a + 3; i++) {
			for (int j = b; j < b + 3; j++) {
				x[i][j] = 1;
			}
		}
	}

	int res = 0;

	for (int i = 1; i <= MAX; i++) {
		for (int j = 1; j <= MAX; j++) {
			if (!x[i][j]) {
				res++;
			}
		}
	}

	printf("%d", res);

	return 0;
}