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

void kill_prev(pid_t *a, int i) {
    for (int j = 1; j < i; j++) {
        kill(a[j], SIGKILL);
    }
    while (wait(NULL) != -1);
    return;
}



int main(int argc, char**argv) {
    if (argc < 2) {
        return 0;
    }
    pid_t pid;
    //всего один процесс
    if (argc == 2) {
        if ((pid = fork()) == 0) {
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        } else if (pid < 0) {
            return 1;
        }
        wait(NULL);
        return 0;
    }



    int fd[2];
    if (pipe(fd)) {
        return 1;
    }

    int fd_tmp;
    pid_t *a = calloc(argc + 1, sizeof(*a));

//первый отдельно
    if ((pid = fork()) == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execlp(argv[1], argv[1], NULL);
        _exit(1);
    } else if (pid < 0) {
        free(a);
        return 1;
    }
    a[1] = pid;

    close(fd[1]);
    fd_tmp = fd[0];

//основной цикл
    for (int i = 2; i < argc - 1; i++) {
        if (pipe(fd)) {
            kill_prev(a, i);
            free(a);
            return 1;
        }
        if ((pid = fork()) == 0) {
            dup2(fd_tmp, 0);
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            close(fd_tmp);
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        } else if (pid < 0) {
            kill_prev(a, i);
            free(a);
            return 1;
        }
        a[i] = pid;
        close(fd_tmp);
        fd_tmp = fd[0];
        close(fd[1]);

    }

//последний тоже отдельно
    if ((pid = fork()) == 0) {
        dup2(fd_tmp, 0);
        close(fd_tmp);

        execlp(argv[argc - 1], argv[argc - 1], NULL);
        _exit(1);
    } else if (pid < 0) {
        kill_prev(a, argc - 1);
        free(a);
        return 1;
    }

    close(fd[0]);
    free(a);
    while (wait(NULL) != -1);

    return 0;
}