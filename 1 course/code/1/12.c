#include <stdio.h>

#define swap(x, y) {int tmp = x; x = y; y = tmp;}

int main(void) {
    int n, a, b, c;
    scanf("%d%d%d%d", &n, &a, &b, &c);

    if (a < b) {
        swap(a, b);
    }
    if (b < c) {
        if (a < c) {
            swap(c, a);
        } 
        swap(b, c);   
    }

    int max1 = a, max2 = b, max3 = c;

    for (int i = 3; i < n; ++i) {
        int x;
        scanf("%d", &x);

        if (x >= max1) {
            max3 = max2;
            max2 = max1;
            max1 = x;
        } else if (x >= max2) {
            max3 = max2;
            max2 = x;
        } else if (x > max3) {
            max3 = x;
        }
    }

    printf("%d %d %d", max1, max2, max3);

    return 0;
}
