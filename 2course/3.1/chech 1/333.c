#include <stdio.h>
#include <stdlib.h>
#define MAX_N 2000

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        return 1;
    }

    if (N > MAX_N) {
        return 1;
    }

    int x;
    int *a = (int*) calloc(N, sizeof(*a));

    if (a == NULL) {
        return 1;
    }

    for (int j = 1; j < N; j++) {
        x = 0;
        while (((j * x) % N) != 1) {
            x++;
        }
        a[j] = x;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < N; j++) {
            printf("%d ", a[j]*i % N);
        }
        printf("\n");
    }

    free(a);

    return 0;
}
