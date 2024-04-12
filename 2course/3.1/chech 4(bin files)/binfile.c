#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>



int main(int argc, char **argv) {
	int f = creat("mybinfile.bin", 0777);
	int fd = open("mybinfile.bin", O_RDWR);

	if (fd == -1) {
		printf("не создал");
		return 0;
	}


	char buf[] = {0x93};
	write(fd, buf, sizeof(char));

	lseek(fd, 0, 0);

//	double x;
//	for (int i = 0; i < 9; i++) {
//		read(fd, &x, sizeof(double));
//		printf("%d ", (int)x);
//	}

	close (fd);

	return 0;
}
