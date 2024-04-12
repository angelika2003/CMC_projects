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

enum
{
    T_LEN = 100
};

int main(int argc, char** argv) {

    int pid = getpid();
    char filename[PATH_MAX];

    char *dir = getenv("XDG_RUNTIME_DIR");
    if (!dir) {
        dir = getenv("TMPDIR");

        if (!dir) {
            dir = "/tmp";
        }
    }
    snprintf(filename, PATH_MAX, "%s/program%d.py", dir, pid);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0700);
    if (fd < 0) {
        return 1;
    }


    unsigned int len = 0;
    for (int i = 1; i < argc; i++) {
        len += strlen(argv[i]);
    }

    len += argc;
    //len++;
    char *str_for_mul = calloc(len, sizeof(char));
    int k = 0;
    for (int i = 1; i < argc; i++) {
        for (int j = 0; j < strlen(argv[i]); j++) {
            str_for_mul[k] = argv[i][j];
            k++;
        }
        str_for_mul[k] = '*';
        k++;
    }
    k--;
    str_for_mul[k] = '\0';

    
    dprintf(fd, "#!/usr/bin/python3\nimport os\nimport sys\n"
        "sys.set_int_max_str_digits(10**6)\n"
        "print(%s)\nos.remove('%s')", str_for_mul, filename);

    free(str_for_mul);
    close(fd);

    execlp(filename, filename, NULL);

    return 1;
}