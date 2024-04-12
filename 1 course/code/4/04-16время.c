#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE (int)(2 * 1e6)

int main(void) {
	char* s = (char*)calloc(BUF_SIZE + 2, sizeof(char));
	scanf("%s", s);

	int len = strlen(s);

	char* res = (char*)calloc(len + 2, sizeof(char));
	strcpy(res, s);

	for (int j = 0; j < len - 1; j++) {
		char* s_new = (char*)calloc(len + 2, sizeof(char));

		for (int i = 0; i < len - 1; i++) {
			s_new[i] = s[i + 1];
		}
		s_new[len - 1] = s[0];

		if (strcmp(res, s_new) > 0) {
			strcpy(res, s_new);
		}

		strcpy(s, s_new);
	}

	printf("%s", res);

	return 0;
}