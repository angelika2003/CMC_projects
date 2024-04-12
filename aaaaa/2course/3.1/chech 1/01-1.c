#include <stdio.h>

int main(void) {
    double x, y;
    if (scanf("%lf%lf", &x, &y) != 2) {
        return 1;
    }

    printf("%d\n", (x >= 2 && x <= 3 && y <= 7 && y >= 1) || (x >= 3 && x <= 5 && y <= 7 && y >= 1 && y >= x - 2));
    
    return 0;
}
