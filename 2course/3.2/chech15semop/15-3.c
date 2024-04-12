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

enum
{
    BASE = 10
};

int main(int argc, char**argv) {

    int n = strtol(argv[1], NULL, BASE);
    int L = strtol(argv[2], NULL, BASE);
    int x;

    int id = semget(IPC_PRIVATE, n, IPC_CREAT | 0666);

    for (int i = 0; i < n; i++) {
        semctl(id, i, SETVAL, 0);
    }


    setbuf(stdin, 0);

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            struct sembuf d = {i, -1, 0};
            int x;


            while (semop (id, &d, 1) >= 0) {

                if (scanf("%d", &x) != -1) {
                    L--;
                    if (L <= 0) {
                        _exit(0);
                    }
                    struct sembuf u_new = {x % n, 1, 0}; ///////
                    printf("%d %d\n", i, L);
                    fflush(stdout);
                    semop (id, &u_new, 1);

                } else {
                    semctl(id, n, IPC_RMID, NULL);
                    _exit(0);
                }
            }
            _exit(0);
        }
    }

    scanf("%d", &x);
    semctl(id, x % n, SETVAL, 1);


    while (wait(NULL) != -1);
    return 0;
}