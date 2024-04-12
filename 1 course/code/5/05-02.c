#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	scanf("%d", &n);

	int size;

	long int max = 0;
	long int cur;

	int** res = NULL;
	int** matrix = NULL;

	int old_size = 0;
	int max_res_size = 0;
	int res_size = 0;

	for (int m_num = 0; m_num < n; ++m_num) {
		scanf("%d", &size);

		if (size > old_size) {
			matrix = (int**)realloc(matrix, size * sizeof(int*));

			for (int i = 0; i < size; ++i) {
				matrix[i] = (int*)realloc(matrix[i], size * sizeof(int));
			}

			old_size = size;
		}

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				scanf("%d", &matrix[i][j]);
			}
		}

		cur = 0;

		for (int i = 0; i < size; ++i) {
			cur += matrix[i][i];
		}

		if (cur > max) {
			max = cur;

			int **tmp = res;
			res = matrix;
			matrix = tmp;

			int t = old_size;
			old_size = max_res_size;
			max_res_size = t;

			res_size = size;
		}
	}

	for (int i = 0; i < res_size; ++i) {
		for (int j = 0; j < res_size; ++j) {
			printf("%d ", res[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < res_size; ++i) {
		free(res[i]);
	}

	free(res);

	for (int i = 0; i < old_size; ++i) {
		free(matrix[i]);
	}

	free(matrix);

	return 0;
}