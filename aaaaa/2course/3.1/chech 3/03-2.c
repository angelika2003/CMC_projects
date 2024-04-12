#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    BASE = 10
};

int main(int argc, char **argv) {
    long long sum1 = 0, sum2 = 0;

    for (int i = 1; i < argc; i++) {
        char *eptr = NULL;
        errno = 0;
        long n = strtol(argv[i], &eptr, BASE);


        if (errno || *eptr || eptr == argv[i] || (int)n != n) {
            return 1;
        }

        if (n > 0) {
            if (__builtin_add_overflow(n, sum1, &sum1)) {
                return 1;
            }
        } else {
            if (__builtin_add_overflow(n, sum2, &sum2)) {
                return 1;
            }
        }
    }

    printf("%lld\n%lld\n", sum1, sum2);
    
    return 0;
}