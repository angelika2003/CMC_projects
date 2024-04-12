#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 102

int main(void) {
	char **telegram = (char**)calloc(sizeof(char*), MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++) {
		telegram[i] = (char*)malloc(sizeof(char) * MAX_SIZE);
	}

	int j = 0;

	while (fgets(telegram[j], 102, stdin)) {
		j++;
	}

	printf("\n"); //

	for (int i = 1; i < j; i += 2) {
		printf("%s", telegram[i]);
	}

	j--;  //на последнюю строку указывает

	if (j % 2 != 0) {
		j--;
	}

	for (int i = j; i >= 0; i -= 2) {
		printf("%s", telegram[i]);
	}

	return 0;
}