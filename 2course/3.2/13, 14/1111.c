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


int main(int argc, char** argv) {
    int fd[2];
    pipe(fd);

    if (!fork()) {
        if (!fork()) {
            if (!fork()) {
                close(fd[0]);
                time_t t = time(NULL);
                write(fd[1], &t, sizeof(t));
                write(fd[1], &t, sizeof(t));
                write(fd[1], &t, sizeof(t));
                close(fd[1]);
                return 0;
            }
            close(fd[1]);
            time_t t;
            read(fd[0], &t, sizeof(t));
            struct tm *time = localtime(&t);

            wait(NULL);
            printf("D:%02d\n", time->tm_mday);
            fflush(stdout); 
            close(fd[0]);
            
            return 0;
        }

        close(fd[1]);
        time_t t;
        read(fd[0], &t, sizeof(t));
        struct tm *time = localtime(&t);

        wait(NULL);
        printf("M:%02d\n", time->tm_mon + 1);
        fflush(stdout); 
        close(fd[0]);
        
        return 0;
    } 

    close(fd[1]);
    time_t t;
    read(fd[0], &t, sizeof(t));
    struct tm *time = localtime(&t);

    wait(NULL);
    printf("Y:%04d\n", time->tm_year + 1900);
    fflush(stdout); 

    close(fd[0]);
    

    return 0;
}