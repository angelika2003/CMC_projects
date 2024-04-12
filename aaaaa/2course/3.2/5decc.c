#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

//семафор Дейкстры (атомарный)---------------------------------------------------------------------------------
//p(down); при попытке уменьшить 0 на 1 - блокировка
//v(up); освобождение ресурса

//если два независ процесса то сначала надо получить ключ:
//key_t ftok(char*fname, char c);
//int semget(key_t key, int n, int fl); возвращ индетиф массива семафоров
//                             IPC_CREAT | 0666(max)
//                             //IPC_EXCL вернет -1 если уже создано
//                             //0 повторно вернет id
//int semctl(int id, int semnum, int cmd, union semun arg);номер семафора  ТОЛЬКО ДЛЯ УДАЛЕНИЯ ИЛИ НАЧ ЗНАЧЕНИЙ
//                               GETVAL вернет текущее значение семафора
//                               SETVAL установить значение, переданное последним аргументом
//                               GETALL
//                               SETALL
//							     IPC_RMID удаление
//                               IPC_STAT
//
//PPPPPPPPPPPPPPPPP неправильноооо тк нет атомарности
//while(!semctl(id, 0, GETVAL, 0));
//semctl(id, 0, SETVAL, 0);

//int semop(int id, struct sembuf *buf, int n);
//{short sem_num;
// short sem_op;
// short sem_flg} 0 (SEM_UNDO) -> будет блокироваться пока отриц
//                IPC_NOWAIT блокировки не будет просто вернет отриц значение
//
//struct sembuf p = {0, -1, 0};
//semop (id, &p, 1);
//struct sembuf v = {0, 1, 0};
//semop (id, &v, 1);

//РАЗДЕЛЯЕМАЯ ПАМЯТЬ-------------------------------------------------------------------------------
//int shmget(key_t key, size_t size, int fl); память в ядре
//
//void* shmat(int id, NULL, 0); подключение - получим норм адрес по которому обращаться(как malloc)
//char* p = shmat
//void* shmdt(p); отключение
//shmctl(id, IPC_RMID, 0); удаление(удалит только когда все закончат работу)


int main(int argc, char**argv) {
	//отец создает двух сыновей, массив семафоров и разд память
	//ввод - печать

	key_t key =  ftok (fname, 0);// IPC_PRIVATEвместо ключа
	int id = semget(key, 2, IPC_CREAT);
	int id_mem = shmget(key, size, IPC_CREAT);
	char* mem = shmat(id_mem, NULL, 0);

	struct sembuf p_0 = {0, -1, 0};
	struct sembuf v_0 = {0, 1, 0};
	struct sembuf p_1 = {1, -1, 0};
	struct sembuf v_1 = {1, 1, 0};

	semctl(id, 0, SETVAL, 1);  //0 запись



	// изнач 1 0
	if (fork() == 0) { //writer
		while (fgets(mem, 256, stdin) != NULL) {

			semop (id, &v_0, 1);

			semop (id, &p_1, 1);

		}
		shmctl(id, IPC_RMID, 0);
	}

	if (fork() == 0) {
		while (semop (id, &p_0, 1) >= 0) {


			printf("%s", mem);

			semop (id, &v_1, 1);
		}


	}

	while (wait(NULL) != -1);

	return 0;
}


