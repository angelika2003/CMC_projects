#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <errno.h>
#include <stdlib.h>

enum
{
    BASE = 10
};

int main(int argc, char **argv) {
//открываем первый файл только для чтения:
    int fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        return 1;
    }
//открываем второй файл для записи:
    int fd_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd_out == -1) {
        return 1;
    }
//третий аргумент число(переводим str to l):
    char *eptr = NULL;
    errno = 0;
    long MOD = strtol(argv[3], &eptr, BASE);

    if (errno || *eptr || eptr == argv[3] || (int)MOD != MOD) {
        return 1;
    }

    if (MOD == 0) {
        close(fd_in);
        close(fd_out);
        return 0;
    }

    long long n = 1;
    char byte;
    while (read(fd_in, &byte, sizeof(char)) == sizeof(char)) {
        for (int i = 0; i < 8; i++) {
            if (byte & 1) {
                int x = (n * (n + 1) * (2 * n + 1) / 6) % MOD;
                write(fd_out, &x, sizeof(int));
            }
            n++;
            byte >>= 1;
        }
    }

    close(fd_in);
    close(fd_out);

    return 0;
}