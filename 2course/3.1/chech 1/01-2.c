#include <stdio.h>

enum
{
    NUM_OF_CHARS = 64,
    MASK_FOR_BIT2 = 0xfffffffb,
    MASK_FOR_BIT3 = 0x8,
    NUM_SHIFT = 1,
    LOWERCASE_SHIFT = NUM_SHIFT + '9' - '0' + 1,
    UPPERCASE_SHIFT = LOWERCASE_SHIFT + 'z'- 'a' + 1
};

int main() {
    char a[NUM_OF_CHARS] = {'@','0','1','2','3','4','5','6','7','8','9',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','#'};

    int c;
    c = getchar();
    int flag = 0;
    while (c != EOF) {
        if (c >= '0' && c <= '9') {
            c = c - '0' + NUM_SHIFT;
            flag = 1;
        }
        else if (c >= 'a' && c <= 'z') {
            c = c - 'a' + LOWERCASE_SHIFT;
            flag = 1;
        }
        else if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + UPPERCASE_SHIFT;
            flag = 1;
        }

        if (flag) {
            c = (c & MASK_FOR_BIT2) ^ MASK_FOR_BIT3;
            putchar(a[c]);
        }

        flag = 0;
        c = getchar();
    }

    return 0;
}