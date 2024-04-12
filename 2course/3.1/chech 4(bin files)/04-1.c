#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>

int main(int argc, char **argv) {
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        return 1;
    }

    unsigned int x;
    while (scanf("%u", &x) == 1) {
        char buf[4];
        buf[0] = x >> 20;
        buf[1] = x << 12 >> 24;
        buf[2] = x << 20 >> 28;
        buf[3] = x;

        if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
            return 1;
        }
    };

    if (close (fd) != 0) {
        return 1;
    }

    return 0;
}
