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

enum
{
    BASE = 16,
    SIZE_OF_FILE = 1 << 16,
    MASK = 0x01FF, //512 - page size
    SHIFT = 9
};

int main (int argc, char** argv) {
    if (argc < 3) {
        return 1;
    }

//файл с проверками:
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    struct stat buf;
    if (fstat(fd, &buf) < 0) {
        return 1;
    }
    if (buf.st_size != SIZE_OF_FILE) {
        return 1;
    }

//адрес начала таблицы:
    char *eptr = NULL;
    errno = 0;
    long table_cp = strtol(argv[2], &eptr, BASE);
    if (errno || *eptr || eptr == argv[2] || (unsigned short)table_cp != table_cp) {
        return 1;
    }
    unsigned short table = (unsigned short)table_cp;


    short *mem = mmap(NULL, SIZE_OF_FILE, PROT_READ, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED) {
        close(fd);
        return 1;
    }

    unsigned short virt_adr, adr, virt_page, page, offset;
    while (scanf("%hx", &virt_adr) == 1) {
        virt_page = virt_adr >> SHIFT;
        offset = virt_adr & MASK;
        page = mem[(table / 2) + virt_page];
        adr = (page) | offset;
        printf("%hu\n", mem[adr / 2]);
    }

//закрываем, очищаем:
    if (munmap (mem, SIZE_OF_FILE) == -1) {
        return 1;
    }
    if (close(fd) != 0) {
        return 1;
    }

    return 0;
}