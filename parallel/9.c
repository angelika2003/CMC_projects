#include <stdio.h>
#include <limits.h>
#include <string.h>

int main ()
{
	char s[LINE_MAX];
	char s_max[LINE_MAX];
	char s_min[LINE_MAX];

	int max_len = 0;
	int min_len = INT_MAX;
	int len = 0;
	int min_index = -1, max_index = -1;
	int index = 1;

	while (scanf("%s", s) != EOF) {
		printf("%s ", s);

		len = strlen(s);
		if (len > max_len) {
			max_len = len;
			strcpy(s_max, s);
			max_index = index;
		}
		if (len < min_len) {
			min_len = len;
			strcpy(s_min, s);
			min_index = index;
		}
		index++;
	}

	printf("\n%s - %d\n", s_max, max_index);
	printf("%s - %d\n", s_min, min_index);

	return 0;
}