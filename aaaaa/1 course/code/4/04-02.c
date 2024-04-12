#include <stdio.h>

#define BUF_SIZE 102

int is_vowel(char c) {
	if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u') || (c == 'y')) {
		return 1;
	}

	if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U') || (c == 'Y')) {
		return 1;
	}

	return 0;
}

int main(void) {
	int n;
	scanf("%d", &n);

	int num_vowels[n];
	for (int i = 0; i < n; i++) {
		scanf("%d\n", &num_vowels[i]);
	}

	for (int i = 0; i < n; i++) {
		char s[BUF_SIZE];
		fgets(s, BUF_SIZE, stdin);

		int n_vowels = 0;
		int prev_isnt_v = 1;

		if (is_vowel(s[0])) {
			n_vowels++;
			prev_isnt_v = 0;
		}

		for (int j = 1; s[j] != '\n'; j++) {
			if (is_vowel(s[j])) {
				if (prev_isnt_v) {
					n_vowels++;
					prev_isnt_v = 0;
				}
			} else {
				prev_isnt_v = 1;
			}
		}

		if (num_vowels[i] == n_vowels) {
			printf("%s", s);
		}
	}

	return 0;
}