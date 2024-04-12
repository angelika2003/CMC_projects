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
#include <sys/mman.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    char*eptr = NULL;
    int n = strtol(argv[1], &eptr, 10 );

    int fd_1[2];
    pipe(fd_1);

    int fd_2[2];
    pipe(fd_2);

    int x = 1;
    write(fd_1[1], &x, sizeof(int));
    //FILE*fw = fdopen(fd_1[1], "w");
    //fprintf(fw, "%d\n", x);
    //fflush(fw);
    //fclose(fw);

    if (n <= 1) {
        close(fd_1[0]);
        close(fd_1[1]);
        close(fd_2[0]);
        close(fd_2[1]);
        printf("Done\n");
        fflush(stdout);
        return 0;
    }

    if (!fork()) { //сын 1
        close(fd_1[1]);
        close(fd_2[0]);
        int pid = 1;
        int a; //можно х использовать тк наследуется
        while (read(fd_1[0], &a, sizeof(int)) != 0) {
            printf("%d %d\n", pid, a);
            fflush(stdout);
            a++;
            if (a == n) {
                close(fd_1[0]);
                close(fd_2[1]);
                return 0;
            }
            write(fd_2[1], &a, sizeof(int));
        }
        close(fd_1[1]);
        close(fd_2[0]);
        return 0;
    }

    if (!fork()) { //сын 2
        close(fd_1[0]);
        close(fd_2[1]);
        int pid = 2;
        int a;
        while (read(fd_2[0], &a, sizeof(int)) != 0) {
            printf("%d %d\n", pid, a);
            fflush(stdout);
            a++;
            if (a == n) {
                close(fd_1[1]);
                close(fd_2[0]);
                return 0;
            }
            write(fd_1[1], &a, sizeof(int));
        }
        close(fd_1[1]);
        close(fd_2[0]);
        return 0;
    }


    close(fd_1[0]);
    close(fd_1[1]);
    close(fd_2[0]);
    close(fd_2[1]);

    while (wait(NULL) != -1);

    printf("Done\n");
    fflush(stdout);
    return 0;
}
