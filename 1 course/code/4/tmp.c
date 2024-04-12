#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pow(x,a) {
	if (a==1){
		return x;
	}
	if (a%2==0){
		c=pow(x,a/2);
		return c*c;
	}



	return x*pow(x,a-1);


}

int main(void) {




	return 0;
}