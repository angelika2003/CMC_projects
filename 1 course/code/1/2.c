#include <stdio.h>

int main(void) {
    int n, x;
    scanf("%d%d", &n, &x);
    
    int max = x;
    int cnt = 1;

    for (int i = 1; i < n; i++) {
        scanf("%d", &x);

        if (x > max) {
            max = x;
            cnt = 1;
        } else if (x == max) {
            cnt++;
        }
    }

    printf("%d", cnt);

    return 0;
}
