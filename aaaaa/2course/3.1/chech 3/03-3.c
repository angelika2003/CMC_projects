#include <stdio.h>
#include <math.h>
#include <stdlib.h>

enum { FOR_ROUND = 10000 };

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    double course;
    char *ptr;
    course = strtod(argv[1], &ptr);
    double p;
    for (int i = 2; i < argc; i++) {
        p = strtod(argv[i], &ptr);
        course = course * (1.0 + p / 100.0);
        course = round((course * FOR_ROUND)) / FOR_ROUND;
    }

    printf("%.4lf\n", course);
    return 0;
}