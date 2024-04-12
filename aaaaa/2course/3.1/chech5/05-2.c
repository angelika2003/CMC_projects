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

enum
{
    BASE = 8
};

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        char *eptr = NULL;
        errno = 0;
        long n = strtol(argv[i], &eptr, BASE);

        if (errno || *eptr || eptr == argv[i] || (int)n != n) {
            return 1;
        }


        char m[] = "rwxrwxrwx"; //вспомогательный массив(можем заменять на "-")
        for (int i = 0 ; i < 9; i++) {
            if ((n & 1) == 0) {
                m[9 - i - 1] = '-';
            }
            n >>= 1;
        }
        printf("%s\n", m);
    }





    return 0;
}


