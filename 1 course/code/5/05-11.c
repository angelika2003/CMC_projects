#include <stdio.h>

int max(unsigned int a, unsigned int b, unsigned int c) {
	unsigned int max;

	if (b > a) {
		max = b;
	} else {
		max = a;
	}

	if (c > max) {
		max = c;
	}

	return max;
}

void res(int N, int M, unsigned int max_sum[][M]) {
	unsigned int res = 0;

	for (int i = 0; i < N; ++i) {
		if (max_sum[i][0] > res) {
			res = max_sum[i][0];
		}
	}

	printf("%u", res);
}


void filling_max_sum(int N, int M, unsigned int plots[][M], unsigned int max_sum[][M], int cur) {
	if (cur == -1) {
		return;
	}

	for (int i = 1; i < N - 1; ++i) {
		unsigned int max_for_cur = max(max_sum[i - 1][cur + 1], max_sum[i][cur + 1], max_sum[i + 1][cur + 1]);
		max_sum[i][cur] = plots[i][cur] + max_for_cur;
	}

	max_sum[0][cur] = plots[0][cur] + max(max_sum[0][cur + 1], max_sum[1][cur + 1], 0);
	max_sum[N - 1][cur] = plots[N - 1][cur] + max(max_sum[N - 1][cur + 1], max_sum[N - 2][cur + 1], 0);

	filling_max_sum(N, M, plots, max_sum, cur - 1);

	return;
}

int main(void) {
	int N, M;
	scanf("%d %d", &N, &M);

	unsigned int plots[N][M];

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%u", &plots[i][j]);
		}
	}

	unsigned int max_sum[N][M];
	for (int i = 0; i < N; ++i) {
		max_sum[i][M - 1] = plots[i][M - 1];
	}

	filling_max_sum(N, M, plots, max_sum, M - 2);

	res(N, M, max_sum);

	return 0;
}