#include <stdio.h>

int is_0_in(int N, int M, int arr[][M + 2]) {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (arr[i][j] == 0) {
				return 1;
			}
		}
	}

	return 0;
}

int main(void) {
	int N, M;
	scanf("%d %d", &N, &M);

	int k;
	scanf("%d", &k);
	int x[k];
	int y[k];
	for (int i = 0; i < k; ++i) {
		scanf("%d %d", &y[i], &x[i]);
	}

	int cells[N + 2][M + 2];
	for (int i = 0; i < N + 2; ++i) {
		for (int j = 0; j < M + 2; ++j) {
			cells[i][j] = 0;
		}
	}

	for (int i = 0; i < k; ++i) {
		cells[x[i]][y[i]] = 1;
	}

	int n = 0;

	while (is_0_in(N, M, cells)) {
		n++;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				if (cells[i][j] == 0) {
					if ((cells[i - 1][j] == n) || (cells[i + 1][j] == n) || (cells[i][j - 1] == n) || (cells[i][j + 1] == n)) {
						cells[i][j] = n + 1;
					}
				}
			}
		}
	}

	printf("%d", n);

	return 0;
}