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
    if ((strlen(srcpath) == 0) || (strlen(dstpath) == 0)) {
        return -1;
    }

//файл открывается, не является дир, есть доступ на чтение
    struct stat buf_1;
    if (stat(srcpath, &buf_1) < 0) {
        return -1;
    }
    if (S_ISDIR(buf_1.st_mode)) {
        return -1;
    }

    int fd_1 = open(srcpath, O_RDONLY);

    if (fd_1 < 0) {
        return -1;
    }

    //printf("file-ok\n");
// ПРАВА ДОСТУПА УЗНАЕМ С ПОМОЩЬЮ BUF_1
    unsigned short p = buf_1.st_mode;
    p &= 0b111111111;
    //printf("p: %u", p);


    struct stat buf_2;
    if (stat(dstpath, &buf_2) < 0) { //создаем сами и перезапись
        //printf("не может открыть agjskdbyierkhfw");
        int fd_2 = open(dstpath, O_WRONLY | O_CREAT | O_TRUNC, p);
        if (fd_2 < 0) {
            return -1;
        }
        int cnt;
        int n = 0;
        int pos;
        char buf[4096];
        while ((cnt = read(fd_1, buf, 4096)) > 0) {
            pos = 0;
            while ((n = write(fd_2, buf + pos, cnt)) > 0) {
                cnt -= n;
                pos += n;
            }
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


            if (dstpath[strlen(dstpath) - 1] == '/') {
                snprintf(path, PATH_MAX + 1, "%s%s", dstpath, sh_name);
            } else {
                snprintf(path, PATH_MAX + 1, "%s/%s", dstpath, sh_name);
            }

            struct stat buf_3;
            if (stat(path, &buf_3) >= 0) {
                if ((buf_1.st_dev == buf_3.st_dev) && (buf_1.st_ino == buf_3.st_ino)) {     //но проверим не лежит ли файл в этой дир
                //printf("%s файл уже есть в этой дир\n", path);
                    return 0;
                } 
            }

            int fd_2 = open(path, O_WRONLY | O_CREAT | O_TRUNC, p);
            if (fd_2 < 0) {
                return -1;
            }

            int cnt;
            int n = 0;
            int pos;
            char buf[4096];
            while ((cnt = read(fd_1, buf, 4096)) > 0) {
                pos = 0;
                while ((n = write(fd_2, buf + pos, cnt)) > 0) {
                    cnt -= n;
                    pos += n;
                }
            }
            return 0;

        } else {

            if ((buf_1.st_dev == buf_2.st_dev) && (buf_1.st_ino == buf_2.st_ino)) {     
                return 0;
            }

            int fd_2 = open(dstpath, O_WRONLY | O_CREAT | O_TRUNC, p);
            if (fd_2 < 0) {
                return -1;
            }

            int cnt;
            int n = 0;
            int pos;
            char buf[4096];
            while ((cnt = read(fd_1, buf, 4096)) > 0) {
                pos = 0;
                while ((n = write(fd_2, buf + pos, cnt)) > 0) {
                    cnt -= n;
                    pos += n;
                }
            }

            //printf("regsoperezapis\n");
            return 0;
        } 

    }

    return 0;
}


//int main(int argc, char **argv) {
//    printf("\n%d\n", copy_file(argv[1], argv[2]));
//    return 0;
//}