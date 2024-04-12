#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int len;
	scanf("%d", &len);

	char * s1 = (char*)malloc(len * sizeof(char) + 1);
	scanf("%s", s1);

	char * s2 = (char*)malloc(len * sizeof(char) + 1) ;
	scanf("%s", s2);

	char * s3 = (char*)malloc(len * sizeof(char) + 1);
	scanf("%s", s3);

	printf("%s", s3);
	printf("%s", s1);
	printf("%s", s2);

	free(s1);
	free(s2);
	free(s3);
	
	return 0;
}