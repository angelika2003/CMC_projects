#include <stdio.h>

void foo(int x[]){
	x[0]+=10;
}

int main(void) {
	int x[] = {1, 2, 5, 7, 9};

	foo(x);
	for (int i = 0; i < 5; ++i)
	{
		printf("%d ", x[i]);
	}


	return 0;
}