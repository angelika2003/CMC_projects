#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <time.h>
int compare_longs(const void* a, const void* b) {
    int arg1 = *(const long long*)a;
    int arg2 = *(const long long*)b;

    if (arg1 > arg2) return 1;
    if (arg1 < arg2) return -1;

    return 0;
}

int main() {
    long long cur = 0;
    int size =10;
    long long *arr = calloc(size, sizeof(long long));

    int i = 0;
    while (scanf("%lld", &cur) == 1) {
        arr[i] = cur;
        i++;
        if(i==size - 1){
            size*=2;
            long long *new_arr = realloc(arr, size*sizeof(long long));
            arr = new_arr;
        }
    }

    qsort(arr, i, sizeof(long long), compare_longs);

    long long sum = 0;

    for (int k = 0; k < i / 2; k++) {
        //printf("%lld\n", arr[k]);
        //printf("%lld\n\n", arr[i - k - 1]);
        sum += arr[k];
        sum += arr[i - k - 1];

    }
    if (i % 2 != 0) {
        sum += arr[i / 2];
    }

    printf("%lld\n", sum);
    free(arr);

    return 0;
}