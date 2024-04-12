#include <stdio.h>
#include <string.h>

#define BYTE 8

int main(void) {
    int c=-5;

    //c=(unsigned)c;
    unsigned char t=-1;

    //printf("%x\n", t);

    printf("%ld", sizeof(BYTE));

    //printf("%x", t<<8);

    return 0;
}
