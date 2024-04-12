#include <stdio.h>
#include <limits.h>

int main ()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int A[n][m];

//считывание матрицы А
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &A[i][j]);
        }
    }

//распечатка двумерного массива А
    printf("Исходная матрица:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    int index_i = -1;
    int index_j = -1;
    int max_neg = INT_MIN;

    for (int j = 0; j < m; j++) {
        for (int i = 0 ; i < n; i++) {
            if (A[i][j] < 0) {
                printf("neg:%d - %d\n", A[i][j], i);
                if (A[i][j] > max_neg) {
                    max_neg = A[i][j];
                    index_j = j;
                    index_i = i;
                }
            }
        }
    }

    if (index_j == -1) {
        printf("problem");
        return 0;
    }

    printf("max: %d - koord: %d %d\n", max_neg, index_i, index_j);

////////////////

    int B[n][m - 1];

    for (int j = 0; j < index_j; j++) {
        for (int i = 0; i < m; i++) {
            B[i][j] = A[i][j];
        }
    }

    for (int j = index_j + 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            B[i][j - 1] = A[i][j];
        }
    }

    printf("NEW матрица:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }






    return 0;
}