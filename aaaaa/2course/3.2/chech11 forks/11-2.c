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

int main (int argc, char** argv) {
    pid_t pid;

    for (int i = 1; i <= 3; i++) {
        if (i == 3) {
            printf("%d ", i);
            return 0;
        }
        if (i != 3 && ((pid = fork()) > 0)) {
            wait(NULL);
            if(i==1){
                printf("%d\n", i);
                return 0;                
            }
            printf("%d ", i);
            return 0;
        }

        if (pid < 0) {
            return 1;
        }
    }

    
    return 0;
}