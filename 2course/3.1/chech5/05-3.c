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

enum
{
    BASE = 8
};


int parse_rwx_permissions(const char *str) {
    if (str == NULL) {
        return -1;
    }

    unsigned int answer = 0;

    char m[] = "rwxrwxrwx";
    int len_m = sizeof(m) - 1;
    int len_str = strlen(str);

    if (len_str != len_m) {
        return -1;
    }

    for (int i = 0; i < len_m; i++) {
        if (str[i] != m[i] && str[i] != '-') {
            return -1;
        } else if (str[i] == m[i]) {
            answer <<= 1;
            answer |= 1;
        } else {
            answer <<= 1;
        }
    }

    return answer;
}
