#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv) {
    char s1[129], s2[129], s3[129];

    scanf("%s", s1);
    scanf("%s", s2);
    scanf("%s", s3);

    printf("[Host:%s,Login:%s,Password:%s]\n", s1, s2, s3);

    return 0;
}