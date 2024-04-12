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
#include <sys/mman.h>

enum
{
    BASE = 10
};

int main (int argc, char** argv) {
    if (argc < 4) {
        return 1;
    }

    char *eptr = NULL;
    errno = 0;
    long rows = strtol(argv[2], &eptr, BASE);
    if (errno || *eptr || eptr == argv[2] || (int)rows != rows) {
        return 1;
    }

    eptr = NULL;
    errno = 0;
    long cols = strtol(argv[3], &eptr, BASE);
    if (errno || *eptr || eptr == argv[3] || (int)cols != cols) {
        return 1;
    }



    int fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0777);
    if (fd < 0) {
        return 1;
    }

    long long res;
    if (__builtin_mul_overflow (rows, cols, &res)) {
        return 1;
    }
    if (__builtin_mul_overflow (res, sizeof(int), &res)) {
        return 1;
    }

    if (ftruncate(fd, res) != 0) {
        return 1;
    }

    int *A = mmap(NULL, res, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (A == MAP_FAILED) {
        return 1;
    }

    int n = cols;
    int m = rows;
    if (n < 0 || m < 0) {
        return 1;
    }

    int i = 1;

    int len_1_0 = 0;
    int len_1 = n - 1;
    int len_2_0 = 0;
    int len_2 = m - 1;

    while (i <= n * m) {
        if (len_1_0 == len_1) {
            for (int j = len_2_0 ; j <= len_2; j++) A[j * n + len_1] = i++;
            break;
        }

        if (len_2_0 == len_2) {
            for (int j = len_1_0; j <= len_1; j++) A[len_2_0 * n + j] = i++;
            break;
        }

        for (int j = len_1_0; j <= len_1; j++) A[len_2_0 * n + j] = i++;
        for (int j = len_2_0 + 1; j <= len_2 - 1; j++) A[j * n + len_1] = i++;
        for (int j = len_1; j >= len_1_0; j--) A[len_2 * n + j] = i++;
        for (int j = len_2 - 1; j >= len_2_0 + 1; j--) A[j * n + len_1_0] = i++;

        len_1_0++;
        len_2_0++;
        len_1--;
        len_2--;
    }

    if (munmap (A, res) == -1) {
        return 1;
    }

    if (close(fd) != 0) {
        return 1;
    }

    return 0;
}