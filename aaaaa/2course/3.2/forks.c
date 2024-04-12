#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char** argv) {

// 1 2 3	
	int n = strtol(argv[1], NULL, 10);
	printf("1\n");

	for (int i = 2; i<=n; i++) {
		if (fork() == 0){  //в сыне
			printf("%d\n", i);
	  	} else {
			wait(NULL);
			return 0;
		}
	}

// CODE FROM DIMAA

	int n;
	pid_t pid;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		printf("%d\n", i);

		if (i != n && ((pid = fork()) != 0)) {
			wait();
			return 0;
		}

		if (pid < 0) {
			return 1;
		}

	}

//в обратном порядке
	int n;
	pid_t pid;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		if (i == n) {
			printf("%d\n", i);
			return 0;
		}
		if (i != n && ((pid = fork()) > 0)) {
			wait();
			printf("%d\n", i);
			return 0;
		}

	}

	return 0;

//

//функция запускает процесс и возвращает успешность завершения	
int f(char *s) {
	pid_t pid =	fork();
	if (pid == 0){
		execlp(s, s, 0);
		_exit(1); //убивает процесс
	} else if (pid < 0) { //считаем что это фатальная ошибка просто выходим
		_exit(1);
	}
	//parent
	int status;
	wait(&status);
	return !(!WIFEXITED(status) || WEXITSTATUS(status)); 	
}

int main (int argc, char** argv) {
	return !((f(argv[1]) || f(argv[2])) && f(argv[3]));
}

ПОСЛЕ ЛЮБОГО ПРИНТФ fflush(stdout);

//запустить трех сыновей каждый считывает по строчке в каком то порядке параллельно должны быть запущены

int main(int argc, char** argv) {
	FILE *f = fopen (argv[1], "r");
	setbuf(f, 0); //обнуляем буфер для правильной работы fgets и это будет наследоваться сыновьями

	for (int i = 1; i <= 3; i++){ //3 сыновей создаём в род процессе
		pid_t pid = fork();
		if (pid == 0) {
			char str[8];
			fgets(str, sizeof(str), f);
			printf("%d %s/n", i, str);
			return 0;
		}
	}

	//просто чтобы отец завершился последним: после всех 3 сыновей
	while (wait(NULL)!=-1);
	return 0;
}

//сыновья формируют один файл
//psss можно забегать за границу, далее заполнить

int main(int argc, char** argv) {
	create
	close();

	for (int i = 1; i <= n; i++){ //параллельная работа процессов
		pid_t pid = fork();
		if (pid == 0) { // son
			int fd = open (argv[1], O_WR); // чтобы у каждого был личный указатель(таблицу вспоминаем)
			lseek(fd, i*sizeof(int), 1);
			///дописать но суть ясна
			write(fd, buf, sizeof(buf));
			return 0;
		}
	}

	//просто чтобы отец завершился последним: после всех 3 сыновей
	while (wait(NULL)!=-1);
	return 0;
}