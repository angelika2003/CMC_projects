#include <stdio.h>

int M(int x, int y, int z){
	if(x<y){
		x^=y;
		y^=x;
		x^=y;	
	} 
		
	while(x>z){


		x^=z;
		z^=x;
		x^=z;
		
		if(x<y){
			
			x^=y;
			y^=x;
			x^=y;	
		} 
	}
	
	return x;
}

int main(void){
	int x, y, z;
	scanf("%d%d%d", &x, &y, &z);
	printf("%d\n", M(x, y, z));

	return 0;
}
