#include <stdio.h>

int main(void) {
    int n, x;
    scanf("%d%d", &n, &x);

    int min, max;
    min = max = x;

    for (int i = 1; i < n; i++) {
        scanf("%d", &x);

        if (x > max) {
            max = x;
        } else if (x < min) {
            min = x;
        }
    }

    printf("%d", max - min);

    return 0;
}
