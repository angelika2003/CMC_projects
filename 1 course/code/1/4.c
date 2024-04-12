#include <stdio.h>

int main(void) {
    int n, x;
    scanf("%d%d", &n, &x);
    
    int len = 1, len_max = 1;

    for (int i = 1; i < n; ++i) {
        int x_prev = x;
        scanf("%d", &x);

        if (x > x_prev) {
            len++;
            if (len > len_max) {
                len_max = len;
            }
        } else {
            len = 1;
        }
    }

    printf("%d", len_max);

    return 0;
}
