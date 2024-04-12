#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char**argv) {
    unsigned size = 0;
    unsigned cur;
    unsigned max = 1;
    unsigned a;
    unsigned a_c;


    while (scanf("%u", &a) == 1) {

        cur = 1;
        a_c = a;
        while ((a_c & 1) == 0) {
            cur <<= 1;
            a_c >>= 1;
        }


        if (cur > max) {
            max = cur;
        }

        size += (cur - size % cur) % cur;
        size += a + (cur - a % cur) % cur;

    }

    size += (max - size % max) % max;

    if (size == 0) {
        size++;
    }

    printf("%u %u\n", size, max);

    return 0;
}