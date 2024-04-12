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

enum
{
    BASE = 10
};

struct Msg
{
    long mtype;
    long long v1;
    long long v2;

};

int main(int argc, char**argv) {

    struct Msg Message;

    int key = strtol(argv[1], NULL, BASE);
    int n = strtol(argv[2], NULL, BASE);
    long long value1 = strtoll(argv[3], NULL, BASE);
    long long value2 = strtoll(argv[4], NULL, BASE);
    long long maxval = strtoll(argv[5], NULL, BASE);

    int msgid = msgget(key, IPC_CREAT | 0666);




    setbuf(stdin, 0);

    int pid;

    for (int i = 0; i < n; i++) {
        if (( pid = fork()) == 0) {
        
            long long value1;
            long long value2;
            long long value3;

            while (msgrcv(msgid, &Message, 256, i+1, 0) >= 0) {

                value1 = Message.v1;
                value2 = Message.v2;

                value3 = value1 + value2;

                printf("%d %lld\n", i, value3);
                fflush(stdout);

                if(abs(value3)>maxval){
                    msgctl(msgid, IPC_RMID, NULL);
                    _exit(0);
                }

                Message.mtype = value3%n+1;
                Message.v1 = value2;
                Message.v2 = value3;
                msgsnd(msgid, &Message, sizeof(struct Msg) - sizeof(long), 0);
            }
            _exit(0);
        } else if (pid < 0) {
            msgctl(msgid, IPC_RMID, NULL);
            while (wait(NULL) != -1);
            return 1;

        }
    }

//запуск только когда все сыновья готовы, иначе при неусп fork может успеть что-то напечатать - WA
    Message.mtype = 1;
    Message.v1 = value1;
    Message.v2 = value2;
    msgsnd(msgid, &Message, sizeof(struct Msg) - sizeof(long), 0);

    while (wait(NULL) != -1);
    return 0;
}
