#include <signal.h>

volatile int cnt = 0;
void(*prev)(int);

void handler (int t) {
	signal(SIGINT, handler);//sistem 5 сбрасывает
	cnt++;
	if (cnt == 4) {
		signal(SIGINT, SIGDFL); //(or prev)
	}
	return;
}

int main() {
	//int kill(pid, int sig);//SIGKILL, SIGINT(ctrl c), SIGCHLD, SIGALARM, SIGPIPE, SIGUSR1, SIGUSR2
	//signal(int sig, void(*f)(int));//возвращает предыд указатель на функцию(SIG_DFL, SIG_DFL)
	prev = signal(SIGINT, handler);

	while (1) pause(); //pause стоит и ждет любого сигнала

	return 0;
}

//ВМЕСТОСИГНАЛ
//int sigaction(int sig, struct sigaction *act, ...*old);
// struct sigaction{
//	void(*sa_handler)(int);
//	int sa_flags; //SA_RESTART
//  ...
//}
int sigaction(SIGINT, &(struct sigaction) {
	.sa_handler = handler;
	.sa_flags = SA_RESTART;
}, NULL);

int sigemptyset (sigset_t *p);//обнуляет маску
int sigaddset(sigset_t *p, int sig);//добавляет этот к маске этот сиг
int sigprocmask(int mode, sigset_t * p, sigset_t * old);
SIG_BLOCK
SIG_UNBLOCK

int sigsuspend (sigset_t *p);//разблокир 1 из заблокированных, который не входит в п


/////////
SIGUSR1 + 5
SIGUSR2 - 4

volatile int cnt;
volatile int flag;

void hand(int sig){
	flag= sig;
}

int main() {
	sigaction(SIGUSR1, &(struct sigaction1) {
		.sa_handler = hand;
		.sa_flags = SA_RESTART;
	}, NULL);

	sigaction(SIGUSR2, &(struct sigaction2) {
		.sa_handler = hand;
		.sa_flags = SA_RESTART;
	}, NULL);


	sigset_t p, old;
	sigemptyset (&p);

	sigaddset (&p, SIGUSR1);
	sigaddset (&p, SIGUSR2);
	sigprocmask(SIGBLOCK, &p, &old);

	printf("PID %d\n", getpid()); тут начнут прилетать сигналы


	while(1) {
        sigsuspend(&old);
        
        if (flag = SIGUSR1) {
            cnt += 5;
            printf(blalala);
            fflush(stdout);
        }
        
        if (flag == SIGUSR2) {
            cnt -= 4;
            printf(balalala);
        }
        
        if (cnt < 0)  {
            return 0;
        }
        
    }

	return 0;
}




