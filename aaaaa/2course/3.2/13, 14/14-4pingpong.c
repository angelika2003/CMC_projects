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

int cnt = 0;
int target_pid, fd[2];
int my_pid;
int max_cnt;

void SigHndlr(int s) {
    my_pid = getpid();
    //printf("%d ", my_pid);
    read(fd[0], &cnt, sizeof(int));

    if (cnt >= max_cnt) {
        fflush(stdout);

        close(fd[0]);
        write(fd[1], &cnt, sizeof(int));
        close(fd[1]);
        kill(target_pid, SIGUSR1);
        _exit(0);
    }

    if (cnt == 0) {
        read(fd[0], &target_pid, sizeof(int));
        cnt++;
        write(fd[1], &cnt, sizeof(int));
        kill(target_pid, SIGUSR1);
        return;
    }

    if (cnt % 2 == 1) {
        printf("1 %d\n", cnt);
        fflush(stdout);
    } else {
        printf("2 %d\n", cnt);
        fflush(stdout);
    }
    cnt++;
    write(fd[1], &cnt, sizeof(int));
    kill(target_pid, SIGUSR1);
    return;

}

enum
{
    BASE = 10
};

int main(int argc, char**argv) {
    max_cnt = strtol(argv[1], NULL, BASE);
    pipe(fd);

    sigaction(SIGUSR1, &(struct sigaction) {\
        .sa_handler = SigHndlr,\
        .sa_flags = SA_RESTART
    }, NULL);

    int p;
    if ((p = fork()) == 0) {

        while (1) {
            pause();
        }
        return 0;
    }

    if (fork() == 0) {
        my_pid = getpid();
        target_pid = p;
        write(fd[1], &cnt, sizeof(int));
        write(fd[1], &my_pid, sizeof(int));
        kill(target_pid, SIGUSR1);
        while (1) {
            pause();
        }
        return 0;
    }

    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    printf("Done\n");
    fflush(stdout);
    return 0;
}