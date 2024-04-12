#include <iostream>
#include <mpi.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <cmath>

using namespace std;

int main(int argc, char ** argv) {
    MPI_Init(&argc, &argv);

    int np;
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    FILE * f_1 = fopen(argv[1], "rb+");
    FILE * f_2 = fopen(argv[2], "rb+");

    __int32_t n;
    fread(&n, sizeof(__int32_t), 1, f_1);
    fread(&n, sizeof(__int32_t), 1, f_2);

//константы для данного процесса номер rank
    int p = pow(np, 1 / 3.0);
    int n_new = n / p;

    int k = rank % p;
    int j = (rank / p) % p;
    int i = (rank / p) / p;

    //cout << rank << ":" << i << " " << j << " " << k << endl;

    if (rank == 0) {
        FILE * f_3 = fopen(argv[3], "wb+");
        fwrite(&n, sizeof(__int32_t), 1, f_3);
        fclose(f_3);
    }

    //MPI_Barrier(comm_K);

//считываем матрицы размера n_new * n_new
    __int32_t *A = (__int32_t *)calloc(n_new * n_new, sizeof(*A));
    __int32_t *B = (__int32_t *)calloc(n_new * n_new, sizeof(*B));
    __int32_t *C = (__int32_t *)calloc(n_new * n_new, sizeof(*C));


    int offset = i * n_new * n + k * n_new + 1;
    fseek(f_1, offset * sizeof(__int32_t), SEEK_SET);
    for (int a = 0; a < n_new; a++) {
        fread(A + a * n_new, sizeof(__int32_t), n_new, f_1);
        fseek(f_1, (n - n_new) * sizeof(__int32_t), SEEK_CUR);

    }

    offset = k * n_new * n + j * n_new;
    fseek(f_2, offset * sizeof(__int32_t), SEEK_CUR);
    for (int a = 0; a < n_new; a++) {
        fread(B + a * n_new, sizeof(__int32_t), n_new, f_2);
        fseek(f_2, (n - n_new) * sizeof(__int32_t), SEEK_CUR);
    }


    /*    printf("\n");
        for (int i_1 = 0; i_1 < n_new; i_1++) {
            for (int j_1 = 0; j_1 < n_new; j_1++) {
                printf("%d ", A[i_1 * n_new + j_1]);
            }
            printf("\n");
        }
        printf("\n");
        for (int i_1 = 0; i_1 < n_new; i_1++) {
            for (int j_1 = 0; j_1 < n_new; j_1++) {
                printf("%d ", B[i_1 * n_new + j_1]);
            }
            printf("\n");
        }*/
    double t1, t2, dt;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i_1 = 0; i_1 < n_new; i_1++) {
        for (int j_1 = 0; j_1 < n_new; j_1++) {
            int s = 0;
            for (int k_1 = 0; k_1 < n_new; k_1++) {
                s += A[i_1 * n_new + k_1] * B[k_1 * n_new + j_1];
            }
            C[i_1 * n_new + j_1] = s;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    dt = duration.count();

    if (rank != 0) {
        MPI_Send(&dt, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        double res = dt;
        double cur;

        for (int i = 1; i < np; i++) {
            MPI_Status status;

            MPI_Recv(&cur, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            if (cur > res) {
                res = cur;
            }
        }
        cout << "Elapsed time: " << res << "s" << endl;
    }

//разделяем на группы с одинак i, j
    int color = rank / p;
    MPI_Comm comm_K;
    MPI_Comm_split(MPI_COMM_WORLD, color, k, &comm_K);

//суммируем в процессе i,j, k=0
    __int32_t *C_sum = (__int32_t *)calloc(n_new * n_new, sizeof(*C_sum));
    MPI_Reduce(C, C_sum, n_new * n_new, MPI_INT32_T, MPI_SUM, 0 , comm_K);


//процесс с k = 0 записывает свой кусочек на выход
    if (rank == i * p * p + j * p) {
        FILE * f_3 = fopen(argv[3], "ab+");

        //матрицу C_sum нужно вписать в файл на позицию i,j
        offset = i * n_new * n + j * n_new + 1;
        cout  << i << " " << j << " " << k << " " << "offset" << offset << " " << C_sum[0] << endl;

        fseek(f_3, offset * sizeof(__int32_t), SEEK_SET);
        for (int a = 0; a < n_new; a++) {
            fwrite(C_sum + a * n_new, sizeof(__int32_t), n_new, f_3);
            fseek(f_3, (n - n_new) * sizeof(__int32_t), SEEK_CUR);
        }

        fclose(f_3);
    }


    fclose(f_1);
    fclose(f_2);
    free(A);
    free(B);
    free(C);
    free(C_sum);
    MPI_Finalize();
    return 0;
}