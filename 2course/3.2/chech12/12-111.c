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
    pid_t pid = fork();
    if (pid < 0) {
        return 0;
    }
    if (!pid) {
        int fd1 = open(argv[2], O_RDONLY);
        if (fd1 < 0) {
            return 42;
        }

        int fd2 = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660);
        if (fd2 < 0) {
            return 42;
        }

        int fd3 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (fd3 < 0) {
            return 42;
        }
        //пересвязка с помощью dup:
        if (dup2(fd1, 0) < 0) {
            return 42;
        }
        //close(fd1);
        if (dup2(fd2, 1) < 0) {
            return 42;
        }
        //close(fd2);
        if (dup2(fd3, 2) < 0) {
            return 42;
        }
        //close(fd3);
        execlp(argv[1], argv[1], NULL);
        return 42;
    }

    int status;
    wait(&status);
    printf("%d\n", status);

    return 0;
}