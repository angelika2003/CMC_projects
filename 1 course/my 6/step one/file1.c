#include <stdio.h>

extern int
fib(int);
static int
fib5(void)
{
	return fib(5);
}

int 
main(void) 
{
	//printf("%d", fib5());
	return 0;
}