#include <stdio.h>

int
fib(int n)
{
	return n > 2 ? fib(n - 1) + fib(n - 2) : 1;
}

int 
main(void) 
{
	return 0;
}