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



volatile unsigned int cnt = 0;
volatile int flag = SIGINT;

void hand(int sig) {
    flag = sig;
}

int main() {
    sigaction(SIGINT, &(struct sigaction) {\
        .sa_handler = hand,\
        .sa_flags = SA_RESTART
    }, NULL);

    sigaction(SIGQUIT, &(struct sigaction) {\
        .sa_handler = hand,\
        .sa_flags = SA_RESTART
    }, NULL);


    printf("%d\n", getpid()); //тут начнут прилетать сигналы
    fflush(stdout);

    int x_c;
    while (scanf("%d", &x_c)==1) {
        unsigned int x = (unsigned int)x_c;
        
        if (flag == SIGINT) {
            cnt+=x;
            printf("%u\n", cnt);
            fflush(stdout);
        }

        if (flag == SIGQUIT) {
            cnt*=x;
            printf("%u\n", cnt);
            fflush(stdout);
        }
    }

    return 0;
}