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

int main (int argc, char** argv) {
    if (argc < 3) {
        return -1;
    }

    DIR* d_1 = opendir(argv[1]);
    if (d_1 == NULL) {
        return -1;
    }

    struct dirent *dd_1;

    unsigned long long sum = 0;

    while ((dd_1 = readdir(d_1)) != NULL) {
        char file_1[PATH_MAX];
        snprintf(file_1, PATH_MAX, "%s/%s", argv[1], dd_1->d_name);

        struct stat buf_1;
        if (lstat(file_1, &buf_1) < 0) { //не следуем симв ссылкам
            continue;
        }

        if (!S_ISREG(buf_1.st_mode) || access(file_1, W_OK) != 0) {
            continue;
        }

        char file_2[PATH_MAX];
        snprintf(file_2, PATH_MAX, "%s/%s", argv[2], dd_1->d_name);
        struct stat buf_2;
        if (stat(file_2, &buf_2) < 0) {
            continue;
        }

        if (buf_1.st_ino == buf_2.st_ino && buf_1.st_dev == buf_2.st_dev) {
            sum += buf_1.st_size;
        }

    }

    if (closedir(d_1) != 0) {
        return -1;
    }

    printf("%lld\n", sum);

    return 0;
}
