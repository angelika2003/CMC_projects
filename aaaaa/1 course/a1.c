#include <stdio.h>

int main(){
	int a[5]={1, 2, 2, 3, 4};

	int i = 2;

	a[i++]*=-1;
	for (int j=0; j<5;j++){
		printf("%d ", a[j]);
	}
	printf("\n");

	i = 0;
	a[0]=1;
	a[1]=2;
	a[i++]=a[i++]*(-1);
	for (int j=0; j<5;j++){
		printf("%d ", a[j]);
	}

	return 0;

}