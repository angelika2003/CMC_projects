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
//открываем файл на чтение и запись:
    int fd = open(argv[1], O_RDWR);

    if (fd == -1) {
        return 1;
    }

//забираем n из кс:
    char *eptr = NULL;
    errno = 0;
    long n = strtol(argv[2], &eptr, BASE);

    if (errno || *eptr || eptr == argv[2] || (int)n != n) {
        close (fd);
        return 1;
    }

    if (n <= 1) {
        close (fd);
        return 0;
    }

    int n_in_file = lseek(fd, 0, 2);
    n_in_file /= sizeof(double);

//начинаем обработку файла:
    lseek (fd, 0, 0);

    if (n > n_in_file) {
        n = n_in_file;
    }

    for (int i = 1; i < n; i++) {
        double num_1, num_2;
        read(fd, &num_1, sizeof(num_1));
        read(fd, &num_2, sizeof(num_2));

        int size = sizeof(num_1);

        lseek (fd, -1 * size, 1);

        num_2 -= num_1;

        write(fd, &num_2, sizeof(double));

        lseek (fd, -1 * size, 1);
    }

    close (fd);
    return 0;
}