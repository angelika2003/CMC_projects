#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE (int)2e6

int main(void) {
	char* s = (char*)calloc(BUF_SIZE + 2, 1);
	scanf("%2000000s", s);

	int len = strlen(s);

	int max_n_0 = 0;
	int curr_n_0 = 0;

	int* indices_0 = (int*)calloc(len, sizeof(int));
	int index = 0;


	for (int i = 0; i < len; ++i) {
		if (s[i] == '0') {
			curr_n_0++;
		} else {
			if (max_n_0 < curr_n_0) {
				max_n_0 = curr_n_0;
				indices_0[0] = i - max_n_0;
				index = 1;
			} else if (max_n_0 == curr_n_0) {
				indices_0[index++] = i - curr_n_0;
			}

			curr_n_0 = 0;
		}
	}


	int n = 0;
	int k = 0;
	while (s[k] == '0') {
		n++;
		k++;
	}
	k = len - 1;
	while (s[k] == '0') {
		n++;
		k--;
	}
	char* res = (char*)calloc(len + 1, 1);
	for (int i_new = 0; i_new < len; ++i_new) {
		res[i_new] = s[(i_new + k+1) % len];
	}	

	if (max_n_0 >= n){
		char* s_new = (char*)calloc(len + 1, 1);

		for (int i = 0; i < index ; ++i) {
			for (int i_new = 0; i_new < len; ++i_new) {
				s_new[i_new] = s[(i_new + indices_0[i]) % len];
			}
			if (strcmp(res, s_new) > 0) {
				strcpy(res, s_new);
			}
		}

		free(s_new);
	}

	printf("%s", res);

	free(res);
	free(indices_0);
	free(s);

	return 0;
}