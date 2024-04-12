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

    int index = -1;

    for (int i = 0; i < n; i++) {
        if (A[i][m - 1] % 2 == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("problem");
        return 0;
    }

    int B[n - 1][m];
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < m; j++) {
            B[i][j] = A[i][j];
        }
    }

    for (int i = index + 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            B[i - 1][j] = A[i][j];
        }
    }

    printf("index: %d", index);

//распечатка двумерного массива B
    printf("Измененная матрица:\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }


    return 0;
}