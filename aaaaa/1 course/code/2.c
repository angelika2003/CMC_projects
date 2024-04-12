#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_spaces(char *s) {
	char *t = s;
	while (*s != '\0') {
		if (*s != ' ') {
			*t = *s;
			t++;
		}
		s++;
	}
	*t = '\0';
}

char *fibocci(char* s) {
	int i1 = 0;
	int i2 = 1;

	int len = strlen(s);

	while (i1 < len) {
		s[i1] = ' ';

		int tmp = i2;
		i2 += i1;
		i1 = tmp;
	}

	remove_spaces(s);

	char* str = (char*)malloc(strlen(s) * sizeof(char));

	int i = 0;
	while (s[i] != '\0') {
		str[i]=s[i];
		i++;
	}

	str[i]='\0';

	free(s);

	return str;
}