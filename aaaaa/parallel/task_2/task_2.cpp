#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <chrono>
#include <assert.h>
#include <errno.h>
#include <sys/time.h>
#include <omp.h>

using namespace std;

int main(int argc, char ** argv) {
    FILE * f_1 = fopen(argv[1], "rb+");
    FILE * f_2 = fopen(argv[2], "rb+");
    FILE * f_3 = fopen(argv[3], "rb+");
    char *eptr = NULL;
    int mode = strtol(argv[4], &eptr, 10);


    int32_t n;
    fread(&n, sizeof(int32_t), 1, f_1);
    fread(&n, sizeof(int32_t), 1, f_2);


    int32_t *A = (int32_t *)calloc(n * n, sizeof(*A));
    int32_t *B = (int32_t *)calloc(n * n, sizeof(*A));
    int32_t *C = (int32_t *)calloc(n * n, sizeof(*A));


    fread(A, sizeof(int32_t), n * n, f_1);
    fread(B, sizeof(int32_t), n * n, f_2);


    int i, j, k;

    auto start = chrono::high_resolution_clock::now();


    if (mode == 0) {
        int num_threads = 4;
        #pragma omp parallel num_threads(num_threads)
        {
            #pragma omp for
            for (i = 0; i < n; ++i) {
                for (j = 0; j < n; ++j) {
                    for (k = 0; k < n; ++k) {
                        C[i * n + j] += A[i * n + k] * B[k * n + j];
                    }
                }
            }
        }
    } else if (mode == 1) {
        int num_threads = 4;
        #pragma omp parallel num_threads(num_threads)
        {
            #pragma omp for
            for (i = 0; i < n; ++i) {
                for (k = 0; k < n; ++k) {
                    for (j = 0; j < n; ++j) {
                        C[i * n + j] += A[i * n + k] * B[k * n + j];
                    }
                }
            }
        }

    } else if (mode == 2) {
        for (k = 0; k < n; ++k) {
            for (i = 0; i < n; ++i) {
                int32_t r = A[i * n + k];
                for (j = 0; j < n; ++j) {
                    C[i * n + j] += r * B[k * n + j];
                }
            }
        }

    } else if (mode == 3) {
        int num_threads = 4;
        #pragma omp parallel num_threads(num_threads)
        {
            #pragma omp for
            for (j = 0; j < n; ++j) {
                for (i = 0; i < n; ++i) {
                    int32_t sum = 0;
                    for (k = 0; k < n; ++k) {
                        sum += A[i * n + k] * B[k * n + j];
                    }
                    C[i * n + j] = sum;
                }
            }
        }

    } else if (mode == 4) {
        for (j = 0; j < n; ++j) {
            for (k = 0; k < n; ++k) {
                for (i = 0; i < n; ++i) {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }

    } else {
        for (k = 0; k < n; ++k) {
            for (j = 0; j < n; ++j) {
                for (i = 0; i < n; ++i) {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }

    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Elapsed time: " << duration.count() << " s" << endl;

    fwrite(&n, sizeof(int32_t), 1, f_3);
    fwrite(C, sizeof(int32_t), n * n, f_3);

    free(A);
    free(B);
    free(C);

    return 0;
}