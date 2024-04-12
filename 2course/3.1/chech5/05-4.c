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

int cmp_names(const void *p1, const void *p2) {
    return (strcmp(*(char **)p1, *(char **)p2));   
}

int main(int argc, char **argv) {
//проверим были ли введены пути к файлам:
    if (argc < 2) {
        return 0;
    }
//массив из указателей на имена
    char **names = (char **)calloc(argc, sizeof(names[0]));

    int cur_i = 0;

    for (int i = 1; i < argc; i++) {

        char *cur = argv[i];
        struct stat cur_buf;
        if (stat(cur, &cur_buf) < 0) {  
            continue;
        }

        int cur_dev = cur_buf.st_dev;
        int cur_ino = cur_buf.st_ino;

        //проверим на наличие такого же пути в нашем массиве:
        int flag = 1;
        for (int k = 0; k < cur_i; k++) {
            struct stat k_buf;
            if (stat(names[k], &k_buf) < 0) {
                continue;
            }

            if ((cur_dev == k_buf.st_dev) && (cur_ino == k_buf.st_ino)) {
                flag = 0;
                if (strcmp(cur, names[k]) > 0) {
                    names[k] = cur;
                    //printf("rewrite(%d)\n", i);
                }
                break;
            }
        }

        //если путь новый(flag == 1), то запишем в names[cur_i]:
        if (flag) {
            names[cur_i] = cur;
            //printf("write new(%d)\n", i);
            cur_i++;
        }

    }

    qsort(names, cur_i, sizeof(names[0]), cmp_names);

    //printf("answerrrr(%d):\n", cur_i);

    for (int i = 0; i < cur_i; i++) {
        printf("%s\n", names[i]);
    }

    free(names);


    return 0;
}