#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE (int)(101+2)

int index_in_str(char* s, char c, int index) {
	for (int i = index; s[i] != '\n'; i++) {
		if (s[i] == c) {
			return i;
		}
	}

	return -1;
}

int main(void) {
	char s[BUF_SIZE];
	fgets(s, BUF_SIZE, stdin);

	int n = 0;

	for (char i1 = '1'; i1 != ':'; i1++) {
		int a = index_in_str(s, i1, 0);

		if (a >= 0) {
			for (int i2 = '0'; i2 != ':'; i2++) {
				int b = index_in_str(s, i2, a + 1);
				
				if (b >= 0) {
					for (int i3 = '0'; i3 != ':'; i3++) {
						int c = index_in_str(s, i3, b + 1);
						if (c >= 0) {
							n ++;
						}
					}
				}
			}
		}
	}

	printf("%d", n);

	return 0;
}