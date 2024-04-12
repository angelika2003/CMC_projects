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
#include <time.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
    pid_t pid;
    int i = 0;
    if ((pid = fork()) == 0) {
        while (scanf("%d", &i) == 1) {
            if ((pid = fork()) > 0) {
                int status;
                wait(&status);
                if (!WIFEXITED(status) || WEXITSTATUS(status)){
                    return 1;
                }
                printf("%d\n", i);
                return 0;

            }
            if (pid < 0) {
                printf("-1");
                return 1;
            }
        }
    } else {
        while (wait(NULL) != -1);
    }   

    return 0;
}