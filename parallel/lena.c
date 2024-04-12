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

    int i_1 = -1, i_2 = -1;//индексы искомых строк
    int sum, max_sum = 0;

    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < m; j++) {
            if (A[i][j] > 0) {
                sum += A[i][j];
            }
        }

        if (sum > max_sum) {
            max_sum = sum;
            i_1 = i;
        }
    }



    int mid;
    int max_mid = INT_MIN;
    int num_neg = 0, sum_neg;

    for (int i = 0; i < n; i++) {
        mid = 0;
        sum_neg = 0;
        num_neg = 0;
        for (int j = 0; j < m; j++) {
            if (A[i][j] < 0) {
                sum_neg += A[i][j];
                num_neg += 1;
            }
        }
        if (num_neg > 0) {
            mid = sum_neg / num_neg;
            if (mid > max_mid) {
                max_mid = mid;
                i_2 = i;
            }
        }
    }

    if (i_1 == -1 || i_2 == -1) {
        printf("problem");
        return 0;
    }

    printf("номера строк: %d %d\n", i_1 + 1, i_2 + 1);

//меняем строки местами
    int tmp;

    for (int j = 0; j < m; j++) {
        tmp = A[i_1][j];
        A[i_1][j] = A[i_2][j];
        A[i_2][j] = tmp;
    }

//распечатка двумерного массива А
    printf("Измененная матрица:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}