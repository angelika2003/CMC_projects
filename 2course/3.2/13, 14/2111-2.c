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

//!!!!!!если скобки то в отдельном сыне
int main(int argc, char** argv) {
    int fd[2];
    pipe(fd);


    if(!fork()){
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        if(!fork()){ 
            int fd_file1 = open(argv[4], O_RDONLY);
            dup2(fd_file1, 0);
            close(fd_file1);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }

        int status;
        wait(&status);
        if (!WIFEXITED(status) || WEXITSTATUS(status)){//условие неуспеха
            return 1;
        }

        if(!fork()){
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }

        wait(NULL);
        _exit(0);
    }

    if(!fork()){ // третий сын параллельно со скобками
        int fd_file2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0700);
        dup2(fd_file2, 1);
        close(fd_file2);
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }


    close(fd[0]);
    close(fd[1]);

    while(wait(NULL)!=-1);

    return 0;
}
