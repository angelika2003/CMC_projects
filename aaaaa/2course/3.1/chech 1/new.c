#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>

int main(int argc, char **argv) {
	unsigned int x;
	scanf("%x", &x);

	printf("%x", x>>16);

	return 0;
}
