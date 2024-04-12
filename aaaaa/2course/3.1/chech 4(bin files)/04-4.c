#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char **argv) {
//открываем файл на чтение и запись:
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        return 1;
    }

    long long cur, min;
    int cur_ind = 0;
    if (read(fd, &min, sizeof(long long)) != sizeof(long long)) {
        close(fd);
        return 0;
    }

    while (read(fd, &cur, sizeof(long long)) == sizeof(long long)) {
        if (cur < min) {
            min = cur;
            cur_ind = lseek(fd, 0, 1) - sizeof(long long);
        }
    }

    if (min > LLONG_MIN) {
        min *= -1;
        lseek(fd, cur_ind, 0);
        write(fd, &min, sizeof(long long));
    }

    close(fd);

    return 0;
}