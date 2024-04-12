#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10000
#define MIN_N 1
#define MAX_M 50000
#define MIN_M 1

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    if (N < MIN_N || N > MAX_N || M < MIN_M || M > MAX_M) {
        return 0;
    }

    int *a = (int*) calloc(N, sizeof(*a));

    int command;
    int L, R;
    int S;

    for (int i = 1; i <= M; i++) {
        scanf("%d", &command);

        if (command == 1) {
            scanf("%d%d%d", &L, &R, &S);
            for (int k = L; k < R; k++) {
                a[k] += S;
            }

        } else {
            scanf("%d%d", &L, &R);
            int summ = 0;
            for (int k = L; k < R; k++) {
                summ += a[k];
            }

            printf("%d\n", summ);
        }
    }

    free(a);

    return 0;
}