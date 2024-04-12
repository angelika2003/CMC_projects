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

int f(char *s) {
    pid_t pid = fork();
    if (pid == 0){
        execlp(s, s, NULL);
        _exit(1); // exit можно вызывать из любой точки программы, 
                            // а return бы вернул бы из f в main
    } else if (pid < 0) { 
        return 0;
    }
    //parent
    int status;
    wait(&status);
    return WIFEXITED(status) && !WEXITSTATUS(status); // 1 если успешно, 0 если не усп
}              


int main(int argc, char** argv) {
    return !((f(argv[1]) || f(argv[2])) && f(argv[3])); //{ cmd1 || cmd2 } && cmd3
}

