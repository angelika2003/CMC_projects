#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

enum
{
    BASE = 10
};

int main(int argc, char **argv) {
    long long sum =0;

    for (int i = 1; i < argc; i++) {
        char *eptr = NULL;
        errno = 0;
        long n = strtol(argv[i], &eptr, BASE);
        if (errno || (*eptr!='+' && *eptr!='-' && *eptr!='k')|| eptr == argv[i] || (int)n != n) {
            continue;
        }

        if (*eptr == '+' && *(eptr+1)=='\0') {
            sum += n;
            
        } else if (*eptr == '-' && *(eptr+1)=='\0') {
            sum -= n;
            
        } else if (*eptr == 'k') {
            long long copy =1000;
            if(__builtin_mul_overflow(copy, n, &copy)){
                continue;
            }

            if (*(eptr+1) == '+' && *(eptr+2)=='\0') {
                sum += copy;
            } else if (*(eptr+1) == '-' && *(eptr+2)=='\0') {
                sum -= copy;
            }
        } else {
            continue;
        }
    }

    printf("%lld\n", sum);



        
    return 0;

}