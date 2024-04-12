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

enum
{
    BASE = 10,
    MIN_ARR_SIZE = 2
};

void recur (char *dir, int level, int max_size, char *sh_dir) {
    //printf ("level %d, %s\n", level, sh_dir);
    if (level > 4) {
        return;
    }

    int arr_size = MIN_ARR_SIZE;
    char **arr = calloc(arr_size, sizeof(*arr));
    int cnt = 0;

    DIR* d = opendir(dir);

    if (d == NULL) {
        return;
    }

    struct dirent *dd;


    while ((dd = readdir(d)) != NULL) {
        //формируем длинное имя содержащегося в директории элемента
        char str[PATH_MAX];
        snprintf(str, PATH_MAX + 1, "%s/%s", dir, dd->d_name);
        //с помощью lstat проверим условия данные в задаче для рег
        struct stat buf;
        if (lstat(str, &buf) < 0) {
            continue;
        }
        if (S_ISREG(buf.st_mode) && !access(str, R_OK) && (buf.st_size <= max_size)) {
            if (level == 1) {
                printf("%s\n", dd->d_name);
            } else {
                char sh_str[PATH_MAX];
                snprintf(sh_str, PATH_MAX + 1, "%s/%s", sh_dir, dd->d_name);
                printf("%s\n", sh_str);
            }
        } else if ((level < 4) && S_ISDIR(buf.st_mode) && strcmp(dd->d_name, ".") && strcmp(dd->d_name, "..")) { // записываем имена dirrss в массив при необходимости resize

            if (cnt == arr_size) {
                arr_size *= 2;
                char **new_arr = realloc(arr, arr_size * sizeof(*new_arr));
                arr = new_arr;
            }

            arr[cnt] = strdup(dd->d_name);
            cnt++;
        }

    }
    closedir(d);
    //бежим по массиву, вызываем recur:
    for (int i = 0; i < cnt; i++) {
        char long_new_dir[PATH_MAX];
        snprintf(long_new_dir, PATH_MAX + 1, "%s/%s", dir, arr[i]);

        if (level == 1) {
            recur(long_new_dir, level + 1, max_size, arr[i]);
        } else {
            char sh_new_dir[PATH_MAX];
            snprintf(sh_new_dir, PATH_MAX + 1, "%s/%s", sh_dir, arr[i]);
            recur(long_new_dir, level + 1, max_size, sh_new_dir);
        }
        free(arr[i]);
    }
    free(arr);

    return;
}

int main(int argc, char **argv) {

    char *eptr = NULL;
    errno = 0;
    long max_size = strtol(argv[2], &eptr, BASE);

    if (errno || *eptr || eptr == argv[2] || (int)max_size != max_size) {
        return 1;
    }

    recur(argv[1], 1, max_size, "");

    return 0;
}