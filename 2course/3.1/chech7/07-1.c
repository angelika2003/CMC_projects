#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

int main() {
    char er[PATH_MAX] = "18446744073709551616";

    char c;
    long long answer = 0;
    int flag = 1;

    while ((c = getc(stdin)) != EOF) {
        if (isspace(c)) {
            if (flag == 0) {
                printf("%lld\n", answer);
                answer = 0;
                flag = 1;
            }
            continue;
        }

        int the_one;
        if (answer <= 0) {
            the_one = -1;
        } else {
            the_one = 1;
        }

        if (__builtin_mul_overflow (answer - the_one, 3, &answer)) {
            printf("%s\n", er);
            while (!isspace(c) && c != EOF) {
                c = getc(stdin);
            }
            if (c == EOF) {
                return 0;
            }
            answer = 0;
            flag = 1;
            continue;
        }

        if (c == 'a') {
            flag = 0;
            if (__builtin_add_overflow (answer, -1 + the_one * 3, &answer)) {
                printf("%s\n", er);
                while (!isspace(c) && c != EOF) {
                    c = getc(stdin);
                }
                if (c == EOF) {
                    return 0;
                }
                answer = 0;
                flag = 1;
            }
        } else if (c == '1') {
            flag = 0;
            if (__builtin_add_overflow (answer, 1 + the_one * 3, &answer)) {
                printf("%s\n", er);
                while (!isspace(c) && c != EOF) {
                    c = getc(stdin);
                }
                if (c == EOF) {
                    return 0;
                }
                answer = 0;
                flag = 1;
            }
        } else if (c == '0') {
            flag = 0;
            if (__builtin_add_overflow (answer, the_one * 3, &answer)) {
                printf("%s\n", er);
                while (!isspace(c) && c != EOF) {
                    c = getc(stdin);
                }
                if (c == EOF) {
                    return 0;
                }
                answer = 0;
                flag = 1;
            }

        }

    }



    if (flag == 0) {
        printf("%lld\n", answer);
    }

    return 0;
}