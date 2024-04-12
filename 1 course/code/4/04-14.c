#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE (int)(1e6+2)

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void) {
	char* s = (char*)calloc(BUF_SIZE, sizeof(char));
	fgets(s, BUF_SIZE, stdin);

	int even_after = 0;
	int odd_after = 0;

	for (int i = 0; (s[i] != '\n') && (s[i] != '\0') ; i += 2) {
		if (s[i] == 'A') {
			even_after++;
		}
	}

	for (int i = 1; (s[i] != '\n') && (s[i] != '\0') ; i += 2) {
		if (s[i] == 'A') {
			odd_after++;
		}
	}

	int even_before = 0;
	int odd_before = 0;

	for (int i = 0; s[i] != '\n'; i++) {
		if (s[i] == 'A') {
			if (i % 2 == 0) {
				if (i == 0) {
					swap(&even_after, &odd_after);
				}

				odd_after--;

				if (odd_before + odd_after == even_before + even_after) {
					printf("%d ", i + 1);
				}

				even_before++;
			} else {
				even_after--;

				if (odd_before + odd_after == even_before + even_after) {
					printf("%d ", i + 1);
				}

				odd_before++;
			}
		} else {
			if (i == 0) {
				swap(&even_after, &odd_after);
			}

			if (odd_before + odd_after == even_before + even_after) {
				printf("%d ", i + 1);
			}
		}
	}
	
	free(s);

	return 0;
}