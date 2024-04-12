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
#include <time.h>
#include <signal.h>

enum
{
    BASE = 10
};

int main(int argc, char**argv) {
    char *eptr = NULL;
    errno = 0;
    long n = strtol(argv[1], &eptr, BASE);

    if (errno || *eptr || eptr == argv[1] || (int)n != n) {
        return 1;
    }

    int res = 0;
    for (int i = 2; i < argc && i < n + 2; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            FILE* f = fopen(argv[i], "r");
            char s[PATH_MAX + 1];
            fgets(s, PATH_MAX, f);
            s[strlen(s) - 1] = '\0';

            execlp(s, s, NULL);
            _exit(1);
        }
    }

    int status;
    while (wait(&status)!= -1){
        res += WIFEXITED(status) && !WEXITSTATUS(status);
    }

    for (int i = n + 2; i < argc; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            FILE* f = fopen(argv[i], "r");
            char s[PATH_MAX + 1];
            fgets(s, PATH_MAX, f);

            s[strlen(s) - 1] = '\0';

            execlp(s, s, NULL);
            _exit(1);
        }
        int status;
        wait(&status);
        res += WIFEXITED(status) && !WEXITSTATUS(status);
    }

    printf("%d\n", res);
    fflush(stdout);

    return 0;
}