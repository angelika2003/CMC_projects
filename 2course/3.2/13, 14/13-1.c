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

volatile int cnt = 0;

void handler (int t) {
    if (cnt == 5) {
        _exit(0);
    }

    printf("%d\n", cnt);
    fflush(stdout);
    cnt++;
    return;
}

int main() {
        sigaction(SIGHUP, &(struct sigaction) {\
        .sa_handler = handler,\
        .sa_flags = SA_RESTART
    }, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    while (1) pause(); //pause стоит и ждет любого сигнала

    return 0;
}