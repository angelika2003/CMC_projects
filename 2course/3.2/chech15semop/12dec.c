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
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>

int main(int argc, char**argv) {
    int N;
    scanf("%d", &N);

    int *fat = calloc(N, sizeof(int));

    for (int i = 2; i <= N - 3; i++) {
        scanf("%d", &fat[i]);
    }

    int i;

    while (scanf("%d", &i) != -1) {
        int cnt = 0;
        if (i == 0 || i == N - 2 || i == N - 1) {
            printf("%d\n", cnt);
            break;
        }
        while (i != 0 && i != N - 2 && i != N - 1) {
            cnt++;
            i = fat[i];
        }

        printf("%d\n", cnt);
    }

    free(fat);

    return 0;
}