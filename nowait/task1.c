#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv) { //аргументы кс 3 файла
	FILE * f_1 = fopen(argv[1], "rb+");
	FILE * f_2 = fopen(argv[2], "rb+");

	__int32_t n;
	fread(&n, sizeof(__int32_t), 1, f_1);
	fread(&n, sizeof(__int32_t), 1, f_2);

	__int32_t *A = (__int32_t *)calloc(n * n, sizeof(*A));
	__int32_t *B = (__int32_t *)calloc(n * n, sizeof(*B));
	__int32_t *C = (__int32_t *)calloc(n * n, sizeof(*C));

	fread(A, sizeof(__int32_t), n * n, f_1);
	fread(B, sizeof(__int32_t), n * n, f_2);

	fclose(f_1);
	fclose(f_2);

	clock_t start_time, end_time;
	double cpu_time_used;

	start_time = clock();

	int num_threads = 4;


	for (int i = 0; i < 10000; ++i) {
		#pragma omp parallel num_threads(num_threads)
		{
			#pragma omp for
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n && A[i * n + j] != 0; j++) {
					C[i * n + j] = A[i * n + j];
				}
			}
		}

		#pragma omp parallel num_threads(num_threads)
		{

			#pragma omp for
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n && B[i * n + j] != 0; j++) {
					C[i * n + j] += B[i * n + j];
				}
			}
		}
	}


	end_time = clock();
	cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Время выполнения: %f секунд\n", cpu_time_used);


// Вывод результата
	FILE * f_3 = fopen(argv[3], "ab+");
	fwrite(C, sizeof(__int32_t), n * n, f_3);

	free(A);
	free(B);
	free(C);
	fclose(f_3);

	return 0;
}