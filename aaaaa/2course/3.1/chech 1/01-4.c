#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 % 2 == 0 && arg2 % 2 == 0) {
        if (arg1 < arg2) return -1;
        if (arg1 > arg2) return 1;
        return 0;
    }
    if (arg1 % 2 == 0 && arg2 % 2 ) {
        return -1;
    }
    if (arg1 % 2 && arg2 % 2 == 0 ) {
        return 1;
    }
    if (arg1 % 2 && arg2 % 2) {
        if (arg1 < arg2) return 1;
        if (arg1 > arg2) return -1;
    }    
    return 0;
}

void sort_even_odd(size_t count, int *data) {
    if (count <= 1) {
        return;
    }

    size_t i = 0;
    size_t j = count - 1;

    while (i < j) {
        if (data[i] % 2 && data[j] % 2 == 0) {
            int t = data[i];
            data[i] = data[j];
            data[j] = t;

            i++;
            if (i == j) {
                break;
            }
            j--;
        }

        else if (data[i] % 2 == 0) {
            i++;
        }

        else if (data[j] % 2) {
            j--;
        }
    }

    if (data[i] % 2 == 0) {
        i++;
    }

    qsort(data, count, sizeof(int), compare_ints);
}