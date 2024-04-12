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
    T_LEN = 1000
};

int main(int argc, char** argv) {

    int pid = getpid();
    char filename[PATH_MAX];
    char out_file[PATH_MAX];
    char *dir = getenv("XDG_RUNTIME_DIR");
    if (!dir) {
        dir = getenv("TMPDIR");

        if (!dir) {
            dir = "/tmp";
        }
    }
    snprintf(filename, PATH_MAX, "%s/program%d.c", dir, pid);
    snprintf(out_file, PATH_MAX, "%s/a%d.out", dir, pid);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        return 1;
    }


    dprintf(fd, "#include <stdio.h>\n"
                "#include <unistd.h>\n"

                "#define summon printf(\"summon\\n\")\n"
                "#define disqualify printf(\"disqualify\\n\")\n"
                "#define reject printf(\"reject\\n\")\n"

                "int main(int argc, char** argv) {\n"
                    "int x;\n"

                    "while (scanf(\"%%d\", &x) != -1) {\n"
                    "%s;\n"
                    "}\n"

                    "unlink(argv[0]);\n"
                "}\n"
                , argv[1]);

    close(fd);

    if(!fork()) {
        execlp("gcc", "gcc", filename, "-o", out_file, NULL);
    }
    wait(NULL);
    execlp(out_file, out_file, NULL);

    return 1;
}