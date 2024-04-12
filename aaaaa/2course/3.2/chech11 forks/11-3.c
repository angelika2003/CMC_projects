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

    for (int i = 1; i <= 3; i++){ //3 сыновей создаём в род процессе
        pid_t pid = fork();
        if (pid == 0) {
            char buf[8];
            read(0, buf, 8);
            long long x = strtoll(buf, NULL, 10);

            printf("%d %lld\n", i, x*x);
            return 0;
        }
    }

    //просто чтобы отец завершился последним: после всех 3 сыновей
    while (wait(NULL)!=-1);
    return 0;
}