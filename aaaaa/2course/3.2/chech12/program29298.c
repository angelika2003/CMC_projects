#include <stdio.h>
#include <stdlib.h>
enum { summon = 1, disqualify = 2, reject = 3 };
int main(int argc, char **argv) {
int x;
int res = 0;
while (scanf("%d", &x) == 1) {
   res = x;
   if (res == 1) {
       printf("summon\n");
       fflush(stdout);
   } else if (res == 2) {
       printf("disqualify\n");
   } else if (res == 3) {
       printf("reject\n");
   }}return 0;
}