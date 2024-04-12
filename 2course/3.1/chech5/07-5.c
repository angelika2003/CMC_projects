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
#include <string.h>
#include <limits.h>

int copy_file(const char *srcpath, const char *dstpath) {

//файл открывается, не является дир, есть доступ на чтение
    struct stat buf_1;
    if (lstat(srcpath, &buf_1) < 0) {
        return -1;
    }
    if (S_ISDIR(buf_1.st_mode)) {

        return -1;
    }
    if (access(srcpath, R_OK) == -1) {
        return -1;
    }

    int fd_1 = open(srcpath, O_RDONLY);

    if (fd_1 < 0) {
        return -1;
    }

    //printf("file-ok\n");
// ПРАВА ДОСТУПА УЗНАЕМ С ПОМОЩЬЮ BUF_1 NORM???
    unsigned short p = buf_1.st_mode;
    p &= 0b111111111;


    struct stat buf_2;
    if (lstat(dstpath, &buf_2) < 0) { //создаем сами и перезапись
        //printf("не может открыть дир");
        int fd_2 = open(dstpath, O_WRONLY | O_CREAT | O_TRUNC, p); 
        int cnt;
        char buf[1024];
        while ((cnt = read(fd_1, buf, 1024)) > 0) {
            write(fd_2, buf, cnt);
        }
        return 0;
    } else {
        if (S_ISDIR(buf_2.st_mode)) { //все норм, создаём копию, path : dstpath/shortname from srcpath
            //printf("dir-ok\n");
            char path[PATH_MAX];
            char sh_name[PATH_MAX];
            int ind = 0;
            for (int i = 0; i < strlen(srcpath); i++) {
                if (srcpath[i] == '/') {
                    ind = i + 1;
                }
            }

            strcpy(sh_name, srcpath + ind);

            snprintf(path, PATH_MAX + 1, "%s/%s", dstpath, sh_name);//НУЖЕН ЛИ / ?????

            if (open(path, O_RDONLY) > 0) {     //но проверим не лежит ли файл в этой дир
                //printf("%s файл уже есть в этой дир\n", path);
                return 0;
            }
            int fd_2 = open(path, O_WRONLY | O_CREAT | O_TRUNC, p); 

            int cnt;
            char buf[1024];
            while ((cnt = read(fd_1, buf, 1024)) > 0) {
                write(fd_2, buf, cnt);
            }
            return 0;

        } else if (S_ISREG(buf_2.st_mode)) {
            int fd_2 = open(dstpath, O_WRONLY);

            int cnt;
            char buf[1024];
            while ((cnt = read(fd_1, buf, 1024)) > 0) {
                write(fd_2, buf, cnt);
            }
            //printf("regsoperezapis\n");
            return 0;

        } else {
            //printf("lstatgoodbutnoregandnodir\n");
            return -1;
        }

    }


    //printf("идиотка?\n");
    return -1;
}


int main(int argc, char **argv) {
    printf("\n%d\n", copy_file(argv[1], argv[2]));
    return 0;
}