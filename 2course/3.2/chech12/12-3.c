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

int f(char *s) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp(s, s, NULL);
        _exit(1);
    } else if (pid < 0) {
        return 1;
    }

    int status;
    wait(&status);
    return !(WIFEXITED(status) && !WEXITSTATUS(status)); // 0 если успешно, 1 если не усп
}
int main(int argc, char** argv) {
    int res = 0;
    int i = 1;
    while (i != argc) {
        if (argv[i][0] == 's') {
            res += !f(argv[i] + 1);
            i++;
        } else if (argv[i][0] == 'p') {
            while (argv[i][0] == 'p') {
                pid_t pid = fork();
                if (pid == 0) {
                    execlp(argv[i] + 1, argv[i] + 1, NULL);
                    return 1;
                }
                i++;
                if (i == argc) {
                    break;
                }
            }
            int status;
            while (wait(&status) != -1) {
                res += WIFEXITED(status) && !WEXITSTATUS(status);
            }
        }
    }

    printf("%d\n", res);
    return 0;
}
