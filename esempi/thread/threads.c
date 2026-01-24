/*
 * Stampa il TID del programma e di tutti i thread creati.
 * 
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

void* start_func(void *arg){

	char *argum = (char*)arg;
	
	printf("\n%s. My TID is: %d.\n", argum, (int)pthread_self());
}

int main(){

	int en;
	pthread_t tid1, tid2;

	char *msg1 = "Hello world. I'm the thread #1.\n";
	char *msg2 = "Hello world. I'm the thread #2.\n";

	//stampa il PID del processo corrente del programma in esecuzione
	printf("\nThe launching process has PID=%d.\n", (int)getpid());

	//stampa il TID del main thread contenuto nel processo corrente
	printf("\nThe launching main thread has TID=%d.\n", (int)pthread_self());

	if((en = pthread_create(&tid1, NULL, start_func, msg1)) != 0){
		errno=en;
		perror("\nErrore creazione primo thread.\n");
		exit(-1);
	}

	if((en = pthread_create(&tid2, NULL, start_func, msg2)) != 0){
		errno=en;
		perror("\nErrore di creazione secondo thread.\n");
		exit(-1);
	}

	if((en = pthread_join(tid1, NULL)) != 0){
		errno = en;
		perror("\nErrore di terminazione primo thread.\n");
		exit(-1);
	}

	if((en = pthread_join(tid2, NULL)) != 0){
		errno = en;
		perror("\nErrore di terminazione secondo thread.\n");
		exit(-1);
	}

	return 0;
}
