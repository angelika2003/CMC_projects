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
#include <time.h>

enum
{
    BASE = 10
};

int main(int argc, char **argv) {

    int y;
    scanf("%d", &y);
    y = y - 1900;


    for (int i = 0; i < 12; i++) {
        int day = 0;


        for (int k = 1; k <= 7; k++) {

            struct tm t = {0, 0, 0, k, i, y, 0, 0, -1};

            mktime(&t);

            if (t.tm_wday == 4) {
                day = k;
                break;
            }

        }

        day += 7;
        while (day <= 31) {
            if (day % 3 != 0) {
                printf("%d %d\n", i + 1, day);
            }
            day += 14;
        }
    }

    return 0;
}