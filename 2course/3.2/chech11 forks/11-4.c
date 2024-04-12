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
#include <time.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
    int n;
    pid_t pid;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        if (i == n) {
            printf("%d\n", i);
            fflush(stdout);
        } else {
            printf("%d ", i);
            fflush(stdout);

        }    

        if (i != n && ((pid = fork()) != 0)) {
            wait(NULL);
            return 0;
        }

        if (pid < 0) {
            return 1;
        }

    }

    return 0;
}


