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

struct Arg
{
    char string[64];
};

//1    Имя динамической библиотеки для загрузки
//2    Имя функции в этой библиотеке
//3    Сигнатура функции
//4,5...    Далее идут аргументы функции (могут отсутствовать)
int main (int argc, char** argv) {
//подгружаем библиотеку
    void *handle = dlopen(argv[1], RTLD_LAZY);
    if (handle == NULL) {
        return 1;
    }
//ищем в ней функцию
    void *f = dlsym(handle, argv[2]);
    if (f == NULL) {
        return 1;
    }
//готовим аргументы для вызова функции
    int index = 0;
    struct Arg* arguments = malloc (sizeof(struct Arg));
    for (int i = 4; i < argc; i++) {
        char c = argv[3][i - 3];
        if (c == 'd') {
            double n = strtod(argv[i], 0);
            memcpy(&(arguments->string[index]), &n, sizeof(n));
            index += sizeof(n);
        } else if (c == 's') {
            char *s = argv[i];
            memcpy(&(arguments->string[index]), &s, sizeof(s));
            index += sizeof(s);
        } else {
            int x = strtol(argv[i], 0, 10);
            memcpy(&(arguments->string[index]), &x, sizeof(x));
            index += sizeof(x);
        }
    }

//вызываем:
    char k = argv[3][0];
    if (k =='v') {
        ((void(*)(struct Arg))(f))(*arguments);
    } else if (k=='i') {
        printf("%d\n", ((int(*)(struct Arg))(f))(*arguments));
    } else if (k=='d') {
        printf("%.10g\n", ((double(*)(struct Arg))(f))(*arguments));
    } else {
        printf("%s\n", ((char*(*)(struct Arg))(f))(*arguments));
    }
 


    free(arguments);

    if (dlclose(handle) != 0) {
        return 1;
    }

    return 0;
}