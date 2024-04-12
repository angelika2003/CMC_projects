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

    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;

    return 0;
}

enum
{
    BASE = 17
};

int main (int argc, char** argv) {

    int size = 10;
    long long *arr = calloc(size, sizeof(long long));
    int i = 0;


    for (int k = 1; k <= argc - 1; k++) {
        char *eptr = NULL;
        long long cur = strtoll(argv[k], &eptr, BASE);

        arr[i] = cur;
        i++;
        if (i == size - 1) {
            size *= 2;
            long long *new_arr = realloc(arr, size * sizeof(long long));
            arr = new_arr;
        }
    }

    qsort(arr, i, sizeof(long long), compare_longs);

    for (int k=0; k<i; k++){
        printf("%lld\n", arr[k]);
    }





    
    free(arr);
return 0;
}