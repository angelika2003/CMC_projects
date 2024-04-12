#include <iostream>
#include <mpi.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <chrono>

using namespace std;

int main(int argc, char ** argv) {//mpirun -np <P> ./prog <P_row> <P_col> <матрица_а> <вектор_b> <вектор_c>
    //MPI::Init(argc, argv); //для исп библиотеки и обменов
    MPI_Init(&argc, &argv);

    int np;
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char *eptr = NULL;
    int P_row = strtol(argv[1], &eptr, 10);
    int P_col = strtol(argv[2], &eptr, 10);

    FILE * f_1 = fopen(argv[3], "rb+");
    FILE * f_2 = fopen(argv[4], "rb+");

    __int32_t m, n;
    /*    if (!fread(&m, sizeof(__int32_t), 1, f_1)) {
            cout << "Error: fread() failed" << endl;
            return 1;
        }
        if (!fread(&n, sizeof(__int32_t), 1, f_1)) {
            cout << "Error: fread() failed" << endl;
            return 1;
        }
        if (!fread(&n, sizeof(__int32_t), 1, f_2)) {
            cout << "Error: fread() failed" << endl;
            return 1;
        }*/
    fread(&m, sizeof(__int32_t), 1, f_1);
    fread(&n, sizeof(__int32_t), 1, f_1);
    fread(&n, sizeof(__int32_t), 1, f_2);

    __int32_t *B = (__int32_t *)calloc(n * 1, sizeof(*B));
    __int32_t *C = (__int32_t *)calloc(m * 1, sizeof(*C));

    /*    if (!fread(B, sizeof(__int32_t), n * 1, f_2)) {
            cout << "Error: fread() failed" << endl;
            return 1;
        }*/
    fread(B, sizeof(__int32_t), n * 1, f_2);

    double t1, t2, dt;
    //t1 = MPI_Wtime();
    auto start = std::chrono::high_resolution_clock::now();

    if (P_col > n) {
        P_col = n;
    }
    if (P_row > m) {
        P_row = m;
    }

    int new_n = n / P_col;
    int n_ost = n % P_col;

    int new_m = m / P_row;
    int m_ost = m % P_row;

    int i = rank / P_col;
    int j = rank % P_col;

    if (j < n_ost) {
        new_n++;
    }
    if (i < m_ost) {
        new_m++;
    }

    int offset = 0;

    if (i < m_ost) {
        offset += i * new_m * n;
    } else {
        offset += m_ost * (new_m + 1) * n + (i - m_ost) * new_m * n ;
    }

    if (j < n_ost) {
        offset += j * new_n;
    } else {
        offset += n_ost * (new_n + 1) + (j - n_ost) * new_n ;
    }


    //std::cout << rank << std::endl;
    __int32_t *A = (__int32_t *)calloc(new_n * new_m, sizeof(*A));

    fseek(f_1, offset * sizeof(__int32_t), 1);

    for (int k = 0; k < new_m; k++) {
        /*        if (!fread(A + k * new_n, sizeof(__int32_t), new_n, f_1)) {
                    cout << "Error: fread() failed" << endl;
                    return 1;
                }*/
        fread(A + k * new_n, sizeof(__int32_t), new_n, f_1);
        fseek(f_1, (n - new_n)*sizeof(__int32_t), 1);
    }
    /*    for (int k = 0; k < new_m; k++) {
            for (int f = 0; f < new_n; f++) {
                cout << A[k * new_n + f] << " ";
            }
            cout << endl;
        }*/

//A new_m*new_n matrix
//B n*1 matrix

    int index_for_b;
    if (j < n_ost) {
        index_for_b = j * new_n;
    } else {
        index_for_b = n_ost * (new_n + 1) + (j - n_ost) * new_n ;
    }

    int index_for_c;
    if (i < m_ost) {
        index_for_c = i * new_m;
    } else {
        index_for_c = m_ost * (new_m + 1) + (i - m_ost) * new_m;
    }

    //std::cout << index_for_b<<" "<<index_for_c << std::endl;

//mult A
    for (int i = 0; i < new_m; i++) {
        C[i] = 0;
        for (int k = 0; k < new_n; k++) {
            C[index_for_c + i] += A[i * new_n + k] * B[index_for_b + k];
        }
    }
    /*    for (int i = 0; i < m; i++) {
            std::cout << C[i] << " ";
        }
        std::cout << endl;*/

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    dt = duration.count();

//C- vector, length:m
    if (rank != 0) {
        MPI_Send(C, m, MPI_INT32_T, 0, 0, MPI_COMM_WORLD);
        //cout << "  " << dt << "s" << endl;
        MPI_Send(&dt, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

//суммирование и вывод ответа в файл
    if (rank == 0) {
        double res = dt;
        double cur;
        FILE * f_3 = fopen(argv[5], "wb+");
        __int32_t *buf = (__int32_t *)calloc(m * 1, sizeof(*buf));
        MPI_Status status;
        for (int i = 1; i < P_col * P_row; i++) {
            MPI_Recv(buf, m, MPI_INT32_T, i, 0, MPI_COMM_WORLD, &status);
            for (int j = 0; j < m; j++) {
                C[j] += buf[j];
            }
            MPI_Recv(&cur, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            if (cur > res) {
                res = cur;
            }
        }
        cout << "Elapsed time: " << res << "s" << endl;
        fwrite(C, sizeof(__int32_t), m, f_3);
        /*        for (int i = 0; i < m; i++) {
                    std::cout << C[i] << " ";
                }
                std::cout << endl;*/
        free(buf);
        fclose(f_3);
    }
    //MPI::Finalize();
    MPI_Finalize();

    fclose(f_1);
    fclose(f_2);
    free(A);
    free(B);
    free(C);

    return 0;
}