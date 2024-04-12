#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    unsigned long long sum = 0;

    for (int i = 1; i < argc; i++) {
        struct stat buf;
        if (lstat(argv[i], &buf) < 0) {
            continue;
        }

        if (S_ISREG(buf.st_mode) && (buf.st_nlink == 1) && (buf.st_size % 1024== 0)) {
            sum+= buf.st_size;
        }
    }

    printf("%llu\n", sum);

    return 0;
}
