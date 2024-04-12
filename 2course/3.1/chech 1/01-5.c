#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10
#define MIN_N 0

void print_array(int arr[], int arr_size) {
    for (int i = 0; i < arr_size; printf("%d", arr[i++]));
    printf("\n");
}

int factorial(int n) {
    return (n == 1) ? 1 : factorial(n - 1) * n;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= MIN_N || n >= MAX_N) {
        return 1;
    }

    int* a = (int*)calloc(n, sizeof(*a));
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    print_array(a, n);


    int i, j;

    for (int k = 1; k <= factorial(n) - 1; k++) {
        i = n - 2;
        j = n - 1;

        while (a[i] > a[i + 1]) {
            i--;
        }

        while (a[i] > a[j]) {
            j--;
        }

        int t = a[i];
        a[i] = a[j];
        a[j] = t;

        for (int st = 1; st <= (n - i) / 2; st++) {
            int l = a[i + st];
            a[i + st] = a[n - st];
            a[n  - st] = l;
        }
        print_array(a, n);

    }

    free(a);


    return 0;
}