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

unsigned char a = 0;
int cnt = 1;
int pid_2;
int pid;


void handler_0(int s) {
    signal(SIGUSR1, handler_0);

    a <<= 1;
    cnt++;
    if (cnt > 8) {
        printf("%c", a);
        fflush(stdout);
        cnt = 1;
        a = 0;
    }
    kill(pid, SIGALRM);

}

void handler_1(int s) {
    signal(SIGUSR2, handler_1);

    a <<= 1;
    a |= 1;
    cnt++;
    if (cnt > 8) {
        printf("%c", a);
        fflush(stdout);
        cnt = 1;
        a = 0;
    }
    kill(pid, SIGALRM);
}

void handler_end(int s) {
    _exit(0);
}

void handler_alrm_par(int s) {
    signal(SIGALRM, handler_alrm_par);
    kill(pid_2, SIGALRM);
}

void handler_for2(int s) {
    signal(SIGALRM, handler_for2);
}

int main(int argc, char**argv) {
    signal(SIGALRM, handler_alrm_par);

    int pid_1;
    pid = getpid();
    if ((pid_1 = fork()) == 0) {
        signal(SIGUSR1, handler_0);
        signal(SIGUSR2, handler_1);
        signal(SIGIO, handler_end);

        while (1) {
            pause(); //приостанавливается до тех пор, пока не получит сигнал
        }
    }


    if ((pid_2 = fork()) == 0) {
        signal(SIGALRM, handler_for2);
        int fd = open(argv[1], O_RDONLY);

        unsigned char c;
        int bit;
        unsigned char mask;

        sigset_t p, old;
        sigemptyset (&p);
        sigaddset(&p, SIGALRM);
        sigprocmask(SIG_BLOCK, &p, &old);

        while (read(fd, &c, sizeof(c)) == sizeof(c)) {

            mask = (char)0x80;
            for (int i = 1; i <= 8; i++) {
                bit = (c & mask);

                if (bit == 0) {
                    kill(pid_1, SIGUSR1);
                } else {
                    kill(pid_1, SIGUSR2);
                }
                
                sigsuspend (&old); //для синхронизации(вместо sigwait)
                                   //blocklist пуст-блок, иначе handler
                mask >>= 1;
            }
        }

        kill(pid_1, SIGIO);
        close(fd);
        _exit(0);

    }

    while (wait(NULL) != -1);

    return 0;
}