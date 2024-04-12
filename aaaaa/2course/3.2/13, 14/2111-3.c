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
    int fd[2];
    pipe(fd);

    if (!fork()) {
        if (!fork()) {
            close(fd[1]);
            unsigned long long sum = 0;
            int y;
            while (read(fd[0], &y, sizeof(y)) != 0) {
                sum += y;
            }
            close(fd[0]);

            printf("%lld\n", sum);
            fflush(stdout); 
            return 0;
        }

        close(fd[1]);
        close(fd[0]);
        wait(NULL);
        return 0;
    } 

    close(fd[0]);
    int x;
    while (scanf("%d", &x) != -1) {
        write(fd[1], &x, sizeof(x));
    }
    close(fd[1]);
    
    wait(NULL);
    return 0;
}