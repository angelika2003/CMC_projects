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

enum
{
    BASE = 10
};

int main (int argc, char** argv) {

    int res = 0;

    int year;
    scanf("%d", &year);

    struct tm t = {0, 0, 0, 1, 0, year - 1900, 0, 0, -1};
    mktime(&t);

    int dop = 1;

    while (t.tm_year == year - 1900) {

        if (t.tm_wday == 0  || t.tm_wday == 6) {
            res++;
        }

        if (dop == t.tm_yday + 1) {
            if (t.tm_wday != 0  && t.tm_wday != 6){
                res++;
            }

            dop*=2;
        }

        t.tm_mday++;
        mktime(&t);
        
    }
    printf("%d\n", res);

    return 0;
}