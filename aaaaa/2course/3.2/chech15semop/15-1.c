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
    int key = strtol(argv[2], NULL, BASE);
    int maxval = strtol(argv[3], NULL, BASE);

    int semid = semget(key, n + 1, IPC_CREAT | 0666);
    int memid = shmget(key, sizeof(int) * 2, IPC_CREAT | 0666);
    int* mem = shmat(memid, NULL, 0);

    for (int i = 0; i <= n; i++) {
        semctl(semid, i, SETVAL, 0);
    }



    mem[0] = 0;
    mem[1] = 0;


    setbuf(stdin, 0);

    for (int i = 1; i <= n; i++) {
        if (fork() == 0) {
            struct sembuf d = {i, -1, 0};

            int val;
            int sender;
            int new_i;

            while (semop (semid, &d, 1) >= 0) {

                val = mem[0];
                sender = mem[1];

                printf("%d %d %d\n", i, val, sender);
                fflush(stdout);

                if (val < maxval) {
                    val++;
                    mem[0] = val;
                    mem[1] = i;
                    
                    val = (unsigned)val;
                    new_i = val % n;
                    new_i*=val;
                    new_i%=n;
                    new_i*=val;
                    new_i%=n;
                    new_i*=val;
                    new_i%=n;

                    struct sembuf u_new = {new_i+ 1, 1, 0};
                    semop (semid, &u_new, 1);

                } else {
                    semctl(semid, n + 1, IPC_RMID, NULL);//удаление массива семафоров
                                                         //все семопы вернут -1 -> завершение
                    _exit(0);
                }
            }
            shmdt(mem);//не обяз
            _exit(0);
        }
    }

    semctl(semid, 1, SETVAL, 1);//начало 

    while (wait(NULL) != -1);
    shmctl(memid, IPC_RMID, NULL);//удаление разд памяти(к этому моменту все сыновья отвязаны и завершены)
    return 0;
}
