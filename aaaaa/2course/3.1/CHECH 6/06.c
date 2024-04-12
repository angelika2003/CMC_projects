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

int main(int argc, char **argv) {

    DIR* d = opendir(argv[1]);

    unsigned long long num = 0;

    struct dirent *dd;
    while ((dd = readdir(d)) != NULL) {
        //формируем длинное имя содержащегося в директории элемента
        char str[PATH_MAX];
        snprintf(str,PATH_MAX, "%s/%s", argv[1], dd->d_name);
        //с помощью stat проверим условия данные в задаче
        struct stat buf;
        if (stat(str, &buf) < 0) {
            continue;
        }
        if (S_ISREG(buf.st_mode) && !access(str, X_OK)) {
            if (!strcmp((dd->d_name + strlen(dd->d_name) - 4), ".exe")) {
                num++;
            }
        }
    }

    printf("%llu\n", num);
    closedir(d);
    return 0;
}
