#include <stdio.h>

#define BUF_SIZE (int)(1e6+2)

int main(void) {
	int K;
	scanf("%d\n", &K);

	char s[BUF_SIZE];
	fgets(s, BUF_SIZE, stdin);

	int n;
	int n_spaces = 0;
	for (n = 0; s[n] != '\n'; n++) {
		if (s[n] == ' ') {
			n_spaces++;
		}
	}

	int sp_for_each = (K - n) / n_spaces + 1;
	int extra_sp = (K - n) % n_spaces;

	for (int i = 0; s[i] != '\n'; i++) {
		if (s[i] != ' ') {
			putchar(s[i]);
		} else if (extra_sp > 0) {
			int n_sp = 1 + sp_for_each;
			for (int i = n_sp; i > 0; i--) {
				printf(" ");
			}
			extra_sp--;
		} else {
			int n_sp = sp_for_each;
			for (int i = n_sp; i > 0; i--) {
				printf(" ");
			}
		}

	}

	return 0;
}