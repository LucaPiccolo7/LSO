/*
 * Scrivere un programma che prende in input un certo numero e genera tanti thread
 * quanti il numero indicato.
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define SIZE 100

void *info_stamp(void *arg){

	printf("\nThread %d, TID=%d.\n", (int)arg, (int)pthread_self());
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

	if(argc != 2){
		perror("\nInserire come argomento un numero.\n");
		exit(-1);
	}

	int n_threads = atoi(argv[1]);
	printf("\nNTHREADS: %d.\n", n_threads);

	pthread_t* tids = (pthread_t*) malloc(n_threads * sizeof(pthread_t));

	int i;
	for(i = 0; i < n_threads; i++){

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		if(pthread_create(tids + i, &attr, info_stamp, (void *)i) != 0){
			perror("\nErrore creazione thread\n");
			exit(-1);
		}

		pthread_attr_destroy(&attr);
	}
	
	pthread_exit(NULL);
}
