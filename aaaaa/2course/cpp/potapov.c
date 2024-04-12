#include <stdio.h>

int main() {
    char str[5];
    scanf("%4s", str);


    __asm(
        "mov %7, %%al\n" //код 4 символа
        "cbw\n" 

        "sub $48, %%ax\n"
        "mov $5, %%bl\n"
        "div %%bl\n" 

        "add $48, %%al\n"
        "add $48, %%ah\n"

        "cmp %5, %%al\n"
        "jnz l\n"
        "cmp %6, %%ah\n"
        "jnz l\n"

        "xor %%bl, %%bl\n"
        "add $48, %%bl\n"

        "cmp %7, %%bl\n"
        "jz end\n"
        "sub $1, %3\n"
        "jmp end\n"


        "l:\n"
        //две последние цифры заменить на первую
        "mov %4 , %%al\n"
        "mov %%al, %2\n"
        "mov %%al, %3\n"

        "end:\n"


        : "=m" (str[0]),"=m" (str[1]), "=m" (str[2]), "=m" (str[3]) //0-3 выход
        : "m" (str[0]),"m" (str[1]), "m" (str[2]), "m" (str[3]) //4-7 вход
    );
    printf("%s\n", str);
    return 0;
}