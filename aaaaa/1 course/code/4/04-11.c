#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 2000 + 2
#define MAX_VALUE 120000

int is_digit(char c) {
	if ((c >= '0') && (c <= '9')) {
		return 1;
	}
	return 0;
}

int is_sign(char c) {
	return (c == '+') || (c == '-') || (c == '/') || (c == '*');
}

int char_to_int(char c) {
	return c - '0';
}

void print_equation(int a, char sign, int b) {
	int c;

	if (sign == '+') {
		c = a + b;
	} else 	if (sign == '-') {
		c = a - b;
	} else if (sign == '/') {
		if (b == 0) {
			return;
		}
		c = a / b;
	} else {
		c = a * b;
	}

	if (c > MAX_VALUE) {
		return;
	}

	printf("%d %c %d = %d\n", a, sign, b, c);
}

int main(void) {
	char* s = (char*)calloc(BUF_SIZE, 1);
	fgets(s, BUF_SIZE, stdin);

	int i = 0;
	while (s[i] != '\n') {
		while (is_digit(s[i]) != 1) {
			i++;
			if (s[i] == '\n') {
				return 0;
			}
		}

		int a = char_to_int(s[i]);
		i++;
		while (is_digit(s[i]) == 1) {
			a = a * 10 + char_to_int(s[i]);
			i++;
		}

		if (!is_sign(s[i])) {
			continue;
		}

		int sign = s[i];
		i++;
		if (is_digit(s[i])) {
			int j = i;
			int b = char_to_int(s[i]);
			i++;
			while (is_digit(s[i]) == 1) {
				b = b * 10 + char_to_int(s[i]);
				i++;
			}
			print_equation(a, sign, b);
			if (is_sign(s[i])) {
				i = j;
			}
		}
	}

	free(s);

	return 0;
}