#include <stdio.h>

#define BUF_SIZE (int)10002

int main(void) {
	char s[BUF_SIZE];
	fgets(s, BUF_SIZE, stdin);

	int len;
	for (len = 0; s[len] != '\n'; len++);

	int period = 1;
	while (period < len) {
		int is_period = 1;

		for (int i = period; i < len; i++) {
			if (s[i] != s[i - period]) {
				is_period = 0;
				break;
			}
		}

		if (is_period) {
			printf("%d ", period);
		}

		period++;
	}

	printf("%d", period);

	return 0;
}