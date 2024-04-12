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

int main() {
    int year;
    scanf("%d", &year);
    year -= 1900;

    struct tm t = {0, 14, 11, 26, 4, 121, 0, 0, -1};

    if (year >= 121) {
        while (t.tm_year != year || t.tm_yday < 256) {
            t.tm_mday += 29;
            t.tm_hour += 12;
            t.tm_min += 44;

            mktime(&t);
        }
    } else {
        while (t.tm_year != (year - 1)) {
            t.tm_mday -= 29;
            t.tm_hour -= 12;
            t.tm_min -= 44;

            mktime(&t);

        }

        while (t.tm_year != year || t.tm_yday < 256) {
            t.tm_mday += 29;
            t.tm_hour += 12;
            t.tm_min += 44;

            mktime(&t);
        }
    }
    int flag = 1;
    while (t.tm_wday != 1) {
        t.tm_mday++;
        mktime(&t);
        flag = 0;
    }

    t.tm_mday += 7 * 3;
    if (flag) {
        t.tm_mday += 7;
        mktime(&t);
    }

    mktime(&t);

    printf("%d-%02d-%02d\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);

    return 0;
}