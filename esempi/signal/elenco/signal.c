#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
void foo(int num_segnale);

int main(){

	signal(SIGUSR1, foo);
	signal(SIGUSR2, foo);
	signal(SIGINT, foo);
	
	if(signal(SIGKILL, foo) == SIG_ERR)
		perror("\nImpossibile intercettare SIGKILL.\n");
	for(;;) { pause(); }

	return 0;
}

void foo(int num_segnale){
	if(num_segnale == SIGINT)
		printf("Segnale INT %d\n", num_segnale);
	if(num_segnale == SIGUSR1)
		printf("Segnale USR1 %d\n", num_segnale);
	if(num_segnale == SIGUSR2)
		printf("Segnale USR2 %d\n", num_segnale);		
	
}
