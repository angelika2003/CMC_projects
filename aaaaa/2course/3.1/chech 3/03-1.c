#include <stdio.h>

STYPE bit_reverse(STYPE value) {
    UTYPE mask = 1;

    int l = 0;
    while (mask != 0) {
        l++;
        mask <<= 1;
    }

    UTYPE new = 0;
    UTYPE value_copy = (UTYPE)value;

    for (int i = 0; i < l; i++) {
        new |= value_copy & 1;

        if (i == l - 1) {
            break;
        }
        value_copy >>= 1;
        new <<= 1;
    }

    return (STYPE)new;
}