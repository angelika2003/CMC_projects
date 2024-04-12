#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <errno.h>

void recur(int fd, int a[3]) {
    if (a[2] != 0) {
        int r[3];
        lseek(fd, a[2] * 3 * sizeof(int), 0);
        read(fd, r, 3 * sizeof(int));
        recur(fd, r);
    }

    printf("%d ", a[0]);

    if (a[1] != 0) {
        int l[3];
        lseek(fd, a[1] * 3 * sizeof(int), 0);
        read(fd, l, 3 * sizeof(int));
        recur(fd, l);
    }

    return;
}


int main(int argc, char **argv) {
//открываем файл только для чтения:    
    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        return 1;
    }
//считываем корень дерева:
    int a[3];
    if (read(fd, a, 3 * sizeof(int))!= 3 * sizeof(int)){
        close(fd);
        return 0;
    }
//бежим рекурсией, сразу печатая:
    recur(fd, a);
    printf("\n");

    close(fd);
    return 0;
}