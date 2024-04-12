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

ssize_t getcwd2(int fd, char *buf, size_t size) {
    char answer[PATH_MAX] = {};
    char tmp_answer[PATH_MAX] = {};

    DIR *g = opendir(".");//для сохранения текущего каталога процесса
    if (g == NULL) {
        return -1;
    }
    int g_fd = dirfd(g);

    if (fchdir(fd) != 0) {
        return -1;
    }

    struct stat prev;
    if (lstat(".", &prev) < 0) {
        return -1;
    }

    struct stat root;
    if (lstat("/", &root) < 0) {
        return -1;
    }

    if (prev.st_ino == root.st_ino && root.st_dev == prev.st_dev) {
        memcpy(answer, "/", 2);
    }

    if (chdir("..") != 0) {
        return -1;
    }
    struct stat cur;
    if (lstat(".", &cur) < 0) {
        return -1;
    }

    while (prev.st_ino != root.st_ino || prev.st_dev != root.st_dev) {
        DIR *p = opendir(".");
        if (p == NULL) {
            return -1;
        }

        struct dirent *dd = NULL;
        while ((dd = readdir(p)) != NULL) {
            struct stat buf;
            char str[PATH_MAX];
            snprintf(str, PATH_MAX, "./%s", dd->d_name);
            if (lstat(str, &buf) < 0) {
                return -1;
            }

            if (buf.st_ino == prev.st_ino && buf.st_dev == prev.st_dev) {
                snprintf(tmp_answer, PATH_MAX, "/%s%s", dd->d_name, answer);
                memcpy(answer, tmp_answer, PATH_MAX);
                break;
            }
        }

        if (closedir(p) != 0) {
            return -1;
        }

        prev = cur;
        if (chdir("..") != 0) {
            return -1;
        }
        if (lstat(".", &cur) < 0) {
            return -1;
        }
    }

    ssize_t len = strlen(answer);
    if (size > 0) {
        snprintf(buf, size, "%s", answer);
    }

    if (fchdir(g_fd) != 0) {
        return -1;
    }

    if (closedir(g) != 0) {
        return -1;
    }

    return len;
}