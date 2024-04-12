#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>

int main(int argc, char **argv) {
	int f = creat("mybinfile.bin", 0666);
	int fd = open("mybinfile.bin", O_RDWR);

	if (fd == -1) {
		printf("не создал");
		return 0;
	}


	int buf[] = {10, 5, 4, -100, 3, 0, 0, 0, 0, -100, 0, 0, 56, 7, 6, -78, 1, 2, 9988, 0, 0, 42, 0, 8, 44, 0, 0 }; 
	write(fd, buf, 27 * sizeof(int));

	lseek(fd, 0, 0);

	int x;
	for (int i = 0; i < 27; i++) {
		read(fd, &x, sizeof(int));
		printf("%d ", x);
	}

	close (fd);

	return 0;
}

