#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>


int
main(int argc, char** argv)
{
    pid_t pid, parent = getpid();
    int num, status;

    while (scanf("%d", &num) != EOF) {
        if ((pid = fork()) > 0) {
            wait(&status);

            if (status != 0) {
                if (parent != getpid()) {
                    exit(1);
                } else {
                    exit(0);
                }
            } else {
                printf("%d\n", num);
                fflush(stdin);
            }

            exit(0);
        } else if (pid < 0) {
            printf("-1\n");
            fflush(stdout);

            exit(1);
        }
    }

    return 0;
}
/*

int main(int argc, char** argv){
//    printf("dfgjk\n");

    pid_t pid = fork();

    pid_t p = getpid();

    printf ("pr:%d fork_returned:%d\n", p, pid);

    int status;
    wait(&status);

    printf ("pr:%d done\n", p);
    return 0;
}
/*
После создания нового дочернего процесса оба процесса будут 
выполнять следующую инструкцию после системного вызова fork().

После успешного завершения fork() возвращает 0 дочернему процессу 
и возвращает идентификатор дочернего процесса родительскому процессу. 

В противном случае родительскому процессу возвращается -1, дочерний процесс не создается, 
а значение errno указывает на ошибку.

Функция wait приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс не завершится
*/
