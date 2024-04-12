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

enum
{
    BITS_IN_BYTE = 8
};

int main(int argc, char **argv) {
    if (argc < 2) {
        return -1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == 0) {
        return -1;
    }

    int max_x = BITS_IN_BYTE * lseek(fd, 0, 2);

    lseek(fd, 0, 0);

    int x;
    int flag = 0;

    while (scanf("%d", &x) == 1) {
        if (x > 0 && x <= max_x) {
            flag = 1;
        } else if (x < 0 && (-1 * x) <= max_x) {
            x *= -1;
            flag = -1;
        } else {
            continue;
        }


        int shift = (x - 1) / BITS_IN_BYTE;
        int n = (x - 1) % BITS_IN_BYTE;

        unsigned char mask = 1;
        for (int i = 1; i <= n; i++) {
            mask <<= 1;
        }

        lseek(fd, shift, 0);
        char bit = 0;
        if (read(fd, &bit, sizeof(bit)) != sizeof(bit)) {
            return -1;
        }

        if (flag == 1) {
            bit |= mask;
        } else if (flag == -1) {
            bit &= (~mask);
        }

        lseek(fd, shift, 0);

        if (write(fd, &bit, sizeof(bit)) != sizeof(bit)) {
            return -1;
        }
    }

    if (close(fd) != 0) {
        return -1;
    }

    return 0;

}
