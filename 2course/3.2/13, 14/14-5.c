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
#include <math.h>


volatile int cnt = 1;
volatile int x = 0;


void handler_1 (int t) {
    if (cnt == 4) {
        _exit(0);
    }

    printf("%d\n", x);
    fflush(stdout);
    cnt++;
    return;
}

void handler_2 (int t) {
    _exit(0);
}

int is_prime(int a) {
    for (int i = 2; i < sqrt(a) + 1; i++) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;

}

int main(int argc, char**argv) {
    int low, high;
    scanf("%d", &low);
    scanf("%d", &high);

    sigaction(SIGINT, &(struct sigaction) {\
        .sa_handler = handler_1, \
        .sa_flags = SA_RESTART
    }, NULL);

    sigaction(SIGTERM, &(struct sigaction) {\
        .sa_handler = handler_2, \
        .sa_flags = SA_RESTART
    }, NULL);

    printf("%d\n", getpid());
    fflush(stdout);



    for (int a = low; a < high; a++) {
        if (is_prime(a)) {
            x = a;
        }
    }

    printf("-1\n");
    fflush(stdout);
    return 0;
}